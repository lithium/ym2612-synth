#include "screen.h" 
#include "gpio.h"



DemoScreen demo_screen;
UiScreen *active_screen = NULL;


void set_active_screen(UiScreen *screen)
{
    active_screen = screen;

    for (int i=0; i < ENCODER_COUNT; i++) {
        encoders[i].setListener(active_screen);
    }
    for (int i=0; i < BUTTON_COUNT; i++) {
        buttons[i].setListener(active_screen);
    }

    touchscreen.setListener(active_screen);

    if (active_screen) {
        active_screen->setDirty();
    }
}


