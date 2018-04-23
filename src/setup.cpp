#include "config.h"
#include "ym2612.h"

void setup()
{

#ifdef SERIAL_DEBUG
    Serial.begin(38400);
    Serial.println("Hello ym2612");
#endif

    ym2612.setup();

    // led
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);
}
