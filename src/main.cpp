#include "config.h"
#include "ym2612.h"

void loop() 
{

    ym2612.write_register(0, 0x28, 0xF0);      // Key on
    delay(1000);
    ym2612.write_register(0, 0x28, 0x00);      // Key off
    delay(1000);
}


