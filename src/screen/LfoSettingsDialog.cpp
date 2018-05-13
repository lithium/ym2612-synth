#include "LfoSettingsDialog.h"
#include "screen.h"



LfoSettingsDialog::LfoSettingsDialog()
{

}

void LfoSettingsDialog::paint()
{
    // dont clear because we're an overlay dialog
    tft.fillRoundRect(dialog_margin,dialog_margin, dialog_width,dialog_height, dialog_radius, COLOR_dialog_background);
    tft.drawRoundRect(dialog_margin+border_padding,dialog_margin+border_padding, dialog_width-border_padding*2,dialog_height-border_padding*2, dialog_radius, COLOR_dialog_border);

    settingsChanged(-1,-1);
    repaint();
}

void LfoSettingsDialog::start()
{
    ym2612.addListener(this);
}
void LfoSettingsDialog::stop()
{
    ym2612.removeListener(this);
}


void LfoSettingsDialog::encoderTurned(int direction, GpioEncoder *e)
{

}
void LfoSettingsDialog::buttonPressed(Button *b)
{
    switch (b->number) {
        case 0:
            UiScreen::setActiveScreen(&voice_settings_dialog);
            break;
        case 1:
            UiScreen::setActiveScreen(&main_screen);
            break;
    }

}
void LfoSettingsDialog::screenTouched(TS_Point p)
{

}
void LfoSettingsDialog::settingsChanged(uint8_t chan, uint8_t oper)
{

}
