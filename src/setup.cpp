#include "config.h"
#include "ym2612.h"
#include "clock.h"
#include "midi.h"

void setup()
{

#ifdef SERIAL_DEBUG
    Serial.begin(38400);
    Serial.println("Hello ym2612");
#endif


    start_clock();

    ym2612.setup();
    ym2612.reset();
    ym2612.segaDocTestProgram(false);

    setup_midi();


    // double blink led for startup
    pinMode(PIN_LED, OUTPUT);
    for (int i=0; i<2; i++) {
        digitalWrite(PIN_LED, HIGH);
        delay(50);
        digitalWrite(PIN_LED, LOW);
        delay(100);
    }
}



