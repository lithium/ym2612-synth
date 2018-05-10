#include "OperatorWidget.h"


OperatorWidget::OperatorWidget()
{

}

void OperatorWidget::paint()
{
    tft.drawRect(x, y, w, h, _active ? ILI9341_WHITE : ILI9341_DARKGREY);
}
