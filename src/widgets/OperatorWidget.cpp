#include "OperatorWidget.h"
#include "ym2612.h"

OperatorWidget::OperatorWidget(int op_number) : op_number(op_number)
{

}

void OperatorWidget::paint()
{
    tft.drawRect(x, y, w, h, _active ? ILI9341_WHITE : ILI9341_DARKGREY);

    auto padding = 4;
    tft.setCursor(x+padding, y+padding);
    tft.setTextSize(2);
    tft.print( ym2612.getMultiple(0, op_number) );
}

void OperatorWidget::setActive(bool active) { 
    _active = active; 
    setDirty(true);
}
