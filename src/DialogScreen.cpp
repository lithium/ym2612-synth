#include "DialogScreen.h"



DialogScreen::DialogScreen()
{

}

void DialogScreen::paint()
{
    // dont clear because we're an overlay dialog
    tft.fillRoundRect(dialog_margin,dialog_margin, dialog_width,dialog_height, dialog_radius, COLOR_dialog_background);
    tft.drawRoundRect(dialog_margin+border_padding,dialog_margin+border_padding, dialog_width-border_padding*2,dialog_height-border_padding*2, dialog_radius, COLOR_dialog_border);
}


