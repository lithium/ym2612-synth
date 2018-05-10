#include "OperatorWidget.h"

static auto padding = 4;
static auto foreground = ILI9341_WHITE;
static auto background = ILI9341_BLACK;

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
    last_patch = new_patch;
}
