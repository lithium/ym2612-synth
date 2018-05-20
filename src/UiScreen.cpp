
#include "UiScreen.h"


UiScreen *active_screen = NULL;


void UiScreen::setActiveScreen(UiScreen *screen)
{
    if (active_screen) {
        active_screen->stop();
    }

    active_screen = screen;

    for (int i=0; i < ENCODER_COUNT; i++) {
        encoders[i].setListener(active_screen);
    }
    // for (int i=0; i < BUTTON_COUNT; i++) {
    //     buttons[i].setListener(active_screen);
    // }
    for (int i=0; i < ANALOG_BUTTON_COUNT; i++) {
        analog_buttons[i].setListener(active_screen);
    }

    touchscreen.setListener(active_screen);

    // ym2612.addListener(active_screen);
    synth.setListener(active_screen);

    if (active_screen) {
        active_screen->start();
        active_screen->setDirty();
    }
}




UiScreen::UiScreen()
{

}    

void UiScreen::loop()
{
}

void UiScreen::start()
{
}

void UiScreen::stop()
{
}

void UiScreen::encoderTurned(int direction, GpioEncoder *e)
{

}
void UiScreen::buttonPressed(Button *b)
{
    
}
void UiScreen::screenTouched(TS_Point p)
{
    
}

void UiScreen::settingsChanged(Ym2612 *ym, uint8_t chan, uint8_t oper)
{
    
}
