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


    paintMultiplier(last_patch.multiplier, foreground);
}

void OperatorWidget::paintMultiplier(uint8_t multiplier, int color)
{
    tft.setTextColor(color);
    tft.setCursor(x+padding, y+padding);
    tft.setTextSize(2);
    tft.print(multiplier);
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
    last_patch = new_patch;
}
