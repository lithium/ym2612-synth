#include "LfoSettingsDialog.h"
#include "screen.h"



LfoSettingsDialog::LfoSettingsDialog()
{

}

void LfoSettingsDialog::paint()
{
    DialogScreen::paint();

    settingsChanged(-1,-1);
    repaint();
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
        case 2:
            UiScreen::setActiveScreen(&patch_dialog);
            break;
    }

}
void LfoSettingsDialog::screenTouched(TS_Point p)
{

}
void LfoSettingsDialog::settingsChanged(uint8_t chan, uint8_t oper)
{

}
