#include "config.h"
#include "ym2612.h"
#include "clock.h"
#include "midi.h"
#include "gpio.h"

void setup()
{
    cli();

#ifdef SERIAL_DEBUG
    Serial.begin(38400);
    Serial.println("Hello ym2612");
#endif


    start_clock();

    ym2612.setup();
    ym2612.reset();

    //initialize all voices with sega doc patch
    for (int i=0; i < 6; i++) {
        ym2612.grandPianoVoice(i);
    }

    setup_midi();




    // double blink led for startup
    pinMode(PIN_LED, OUTPUT);
    for (int i=0; i<2; i++) {
        digitalWrite(PIN_LED, HIGH);
        delay(50);
        digitalWrite(PIN_LED, LOW);
        delay(100);
    }


    setup_gpio();
    sei();
}



