#include "config.h"
#include "ym2612.h"
#include "gpio.h"
#include "screen.h"


void loop() 
{
    usbMIDI.read();

    check_encoders();

    if (active_screen && active_screen->isDirty()) {
        active_screen->paint();
        active_screen->setDirty(false);
    }
}


