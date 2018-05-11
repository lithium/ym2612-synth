#include "OperatorWidget.h"

static auto padding = 4;
static auto foreground = ILI9341_WHITE;
static auto background = ILI9341_BLACK;
static auto border_width = 2;

static auto tl_stroke_color = ILI9341_LIGHTGREY;
static auto sl_stroke_color = ILI9341_DARKGREY;
static auto env_stroke_color = ILI9341_WHITE;

OperatorWidget::OperatorWidget(int op_number) : op_number(op_number)
{
    memset(&last_patch, 0, sizeof(last_patch));
}

void OperatorWidget::paint()
{
    tft.drawRect(x, y, w, h, _active ? ILI9341_WHITE : ILI9341_DARKGREY);


    // multiplier label
    tft.setTextColor(ILI9341_LIGHTGREY);
    tft.setCursor(x+padding, y+padding+7);
    tft.setTextSize(1);
    tft.print("x");

    paintMultiplier(last_patch.multiplier, foreground);
    paintDetune(last_patch.detune, foreground);
    paintEnvelope(last_patch);
}

void OperatorWidget::paintMultiplier(uint8_t multiplier, int color)
{
    tft.setTextColor(color);

    if (multiplier == 0) { 
        // 0 == x1/2
        tft.setTextSize(1);
        tft.setCursor(x+padding+6, y+padding);
        tft.print("1");

        tft.drawLine(x+padding+10, y+padding+10, x+padding+14, y+padding+4, color);

        tft.setCursor(x+padding+16, y+padding+8);
        tft.print("2");
    } else {
        tft.setTextSize(2);
        tft.setCursor(x+padding+8, y+padding);
        tft.print(multiplier);
    }
}

void OperatorWidget::paintDetune(uint8_t detune, int color)
{
    if (detune == 0 || detune == 0b100) {
        return; 
    }

    tft.setTextSize(1);
    tft.setTextColor(color);
    tft.setCursor(x+42, y+7);
    tft.print(detune & 0b100 ? "-" : "+");

    tft.setTextSize(2);
    tft.setCursor(x+50, y+padding);
    tft.print(detune & 0b11);
}


void drawLabeledLine(int x1, int y1, int x2, int y2, int label, int color)
{
    auto midx = (x1+x2)/2;
    auto midy = (y1+y2)/2;
    auto labelWidth = 10;
    auto labelHeight = 20;

    tft.drawLine(x1, y1, x2, y2, color); 
    // tft.fillRect(midx-labelWidth/2, midy-labelHeight/2, labelWidth, labelHeight, background);
    tft.setTextSize(1);
    tft.setTextColor(color);
    tft.setCursor(midx - labelWidth/2, midy);
    tft.print(label);
}
void OperatorWidget::paintEnvelope(struct ym2612_patch_op_t env, bool erase)
{
    auto env_top = y + 20;
    auto bottom = y + h - border_width;
    auto right = x + w - border_width*2;
    auto env_height = bottom - env_top;
    auto env_width = w - border_width*2; 
    float norm_tl = (float)(127 - env.total_level) / 127.0;
    float norm_sl = (float)(15 - env.sustain_level) / 15.0;
    float norm_ar = (float)(31 - env.attack_rate) / 31;
    float norm_dr = (float)(31 - env.decay_rate) / 31;
    float norm_sr = (float)(31 - env.sustain_rate) / 31;
    float norm_rr = (float)(15 - env.release_rate) / 15;

    auto tl_y = bottom - env_height*norm_tl;
    auto sl_y = bottom - env_height*norm_sl;

    auto ar_x = x + border_width + (norm_ar * (env_width/3));
    auto dr_x = ar_x + (norm_dr * (env_width/3));

    auto sr_y = bottom - (norm_rr * (env_height/6));
    auto remain_x = x + env_width - dr_x - (norm_rr * (env_height/6));
    if (env.release_rate == 0) {
        remain_x = right - dr_x;
        sr_y = bottom;
    }
    auto sr_x = dr_x + (norm_sr * remain_x);

    if (env.attack_rate == 0) {
        // envelope never starts if ar = 0
        tl_y = bottom;
    }

    if (env.decay_rate == 0) {
        //no decay if dr = 0
        sl_y = tl_y;
    }

    if (env.sustain_rate == 0) {
        // no sustain decay if sr = 0
        sr_y = sl_y;
    }

    if (sl_y < tl_y) {
        // sustain level is always lower than total level
        sl_y = tl_y;
    }
    if (sr_y < sl_y) {
        // release level is below sustain level
        sr_y = sl_y;
    }


    // total level
    // tft.drawFastHLine(x + border_width, tl_y, w - border_width*2, erase ? background : tl_stroke_color);

    // sustain level
    // tft.drawFastHLine(x + border_width, sl_y, w - border_width*2, erase ? background : sl_stroke_color);

    drawLabeledLine(x + border_width, bottom, ar_x, tl_y, env.attack_rate, erase ? background : env_stroke_color);
    drawLabeledLine(ar_x, tl_y, dr_x, sl_y, env.decay_rate, erase ? background : env_stroke_color);
    drawLabeledLine(dr_x, sl_y, sr_x, sr_y, env.sustain_rate, erase ? background : env_stroke_color);
    drawLabeledLine(sr_x, sr_y, right, bottom, env.release_rate, erase ? background : env_stroke_color);
}


void OperatorWidget::setActive(bool active) { 
    _active = active; 
    setDirty(true);
}

void OperatorWidget::operatorChanged(struct ym2612_patch_op_t new_patch)
{
    if (last_patch.multiplier != new_patch.multiplier) {
        paintMultiplier(last_patch.multiplier, background);
        paintMultiplier(new_patch.multiplier, foreground);
    }
    if (last_patch.detune != new_patch.detune) {
        paintDetune(last_patch.detune, background);
        paintDetune(new_patch.detune, foreground);
    }

    if (
        (last_patch.total_level != new_patch.total_level) ||
        (last_patch.sustain_level != new_patch.sustain_level) ||
        (last_patch.attack_rate != new_patch.attack_rate) ||
        (last_patch.decay_rate != new_patch.decay_rate) ||
        (last_patch.sustain_rate != new_patch.sustain_rate) ||
        (last_patch.release_rate != new_patch.release_rate)
        ) {
        paintEnvelope(last_patch, true);
        paintEnvelope(new_patch, false);
    }
    last_patch = new_patch;
}
