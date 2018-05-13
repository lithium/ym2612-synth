#include "OperatorWidget.h"


static auto padding = 4;
static auto foreground = ILI9341_WHITE;

static auto active_background = COLOR_darkgrey;
static auto unactive_background = COLOR_lightgrey;

static auto border_width = 2;

static auto attack_color = ILI9341_BLUE;
static auto decay_color = ILI9341_GREEN;
static auto sustain_color = ILI9341_CYAN;
static auto release_color = ILI9341_MAGENTA;

OperatorWidget::OperatorWidget(int op_number) : op_number(op_number)
{
    memset(&last_patch, 0, sizeof(last_patch));
}

void OperatorWidget::paint()
{
    tft.fillRect(x,y,w,h, _active ? active_background : unactive_background);
    emboss_frame(x,y,w,h, _active ? COLOR_emboss : COLOR_deboss);


    // multiplier label
    tft.setFont(ComicSansMS_10);
    tft.setTextColor(foreground);
    tft.setCursor(x+padding, y+padding+3);
    tft.print("x");

    paintMultiplier(last_patch.multiplier, foreground);
    paintDetune(last_patch.detune, foreground);
    paintEnvelope(last_patch);
}

void OperatorWidget::paintMultiplier(uint8_t multiplier, int color)
{
    tft.setTextColor(color);
    tft.setFont(ComicSansMS_14);

    tft.setCursor(x+padding+10, y+padding);
    if (multiplier == 0) { 
        tft.print("1/2");
    } else {
        tft.print(multiplier);
    }
}

void OperatorWidget::paintDetune(uint8_t detune, int color)
{
    if (detune == 0 || detune == 0b100) {
        return; 
    }

    tft.setTextColor(color);
    tft.setFont(ComicSansMS_14);

    tft.setCursor(x+50, y+padding);
    tft.print(detune & 0b100 ? "-" : "+");
    tft.print(detune & 0b11);
}


inline void drawLabeledLine(int x1, int y1, int x2, int y2, int label, int color)
{
    auto midx = (x1+x2)/2;
    auto midy = (y1+y2)/2;
    auto labelWidth = 10;
    auto labelHeight = 20;

    tft.drawLine(x1, y1, x2, y2, color); 
    // tft.fillRect(midx-labelWidth/2, midy-labelHeight/2, labelWidth, labelHeight, background);
    // tft.setTextSize(1);
    // tft.setTextColor(color);
    // tft.setCursor(midx - labelWidth/2, midy);
    // tft.print(label);
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

    auto background = _active ? active_background : unactive_background;

    //attack
    tft.fillTriangle(x+border_width,bottom, ar_x,tl_y, ar_x,bottom, erase ? background : attack_color);

    //decay
    tft.fillTriangle(ar_x,bottom, ar_x,tl_y, dr_x,sl_y, erase ? background : decay_color);
    tft.fillTriangle(ar_x,bottom, dr_x,bottom, dr_x,sl_y, erase ? background : decay_color);

    //sustain
    tft.fillTriangle(dr_x,bottom, dr_x,sl_y, sr_x,sr_y, erase ? background : sustain_color);
    tft.fillTriangle(dr_x,bottom, sr_x,bottom, sr_x,sr_y, erase ? background : sustain_color);

    //release 
    tft.fillTriangle(sr_x,bottom, sr_x,sr_y, right,bottom, erase ? background : release_color);
}


void OperatorWidget::setActive(bool active) { 
    _active = active; 
    setDirty(true);
}

void OperatorWidget::operatorChanged(struct ym2612_patch_op_t new_patch)
{
    if (last_patch.multiplier != new_patch.multiplier) {
        paintMultiplier(last_patch.multiplier, _active ? active_background : unactive_background);
        paintMultiplier(new_patch.multiplier, foreground);
    }
    if (last_patch.detune != new_patch.detune) {
        paintDetune(last_patch.detune, _active ? active_background : unactive_background);
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
