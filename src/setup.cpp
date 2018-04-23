#include "config.h"
#include "ym2612.h"
#include "clock.h"

void setup()
{

#ifdef SERIAL_DEBUG
    Serial.begin(38400);
    Serial.println("Hello ym2612");
#endif

    start_clock();

    ym2612.setup();
    ym2612.reset();
    ym2612.segaDocTestProgram();

    // led
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);
}



