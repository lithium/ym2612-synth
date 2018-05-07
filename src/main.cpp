#include "config.h"
#include "ym2612.h"
#include "gpio.h"

void loop() 
{
    usbMIDI.read();

    check_encoders();
}


