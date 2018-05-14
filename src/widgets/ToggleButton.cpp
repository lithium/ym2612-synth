#include "ToggleButton.h"


void ToggleButton::paint()
{
    tft.fillRect(x+2,y+2,w-2,h-2, COLOR_lightgrey);

    emboss_frame(x,y,w,h, _active ? COLOR_emboss : COLOR_deboss);

    padding_left = 4;
    padding_top = 4;

    Label::paint();
}
