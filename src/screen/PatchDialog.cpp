#include "PatchDialog.h"
#include "screen.h"



PatchDialog::PatchDialog()
{

}

void PatchDialog::paint()
{
    DialogScreen::paint();

    settingsChanged(nullptr,-1,-1);
    repaint();
}


void PatchDialog::encoderTurned(int direction, GpioEncoder *e)
{

}
void PatchDialog::buttonPressed(Button *b)
{
    switch (b->number) {
        case 0:
            UiScreen::setActiveScreen(&voice_settings_dialog);
            break;
        case 1:
            UiScreen::setActiveScreen(&lfo_settings_dialog);
            break;
        case 2:
            UiScreen::setActiveScreen(&main_screen);
            break;
    }

}
void PatchDialog::screenTouched(TS_Point p)
{

}
void PatchDialog::settingsChanged(Ym2612 *ym, uint8_t chan, uint8_t oper)
{

}
