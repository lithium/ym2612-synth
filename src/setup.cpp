#include "config.h"
#include "ym2612.h"
#include "clock.h"
#include "midi.h"
#include "gpio.h"
#include "screen.h"

#include "internal_storage.h"

#include <SD.h>
#include <SPI.h>
#include <Wire.h>

void test_sdcard()
{
    pinMode(10, OUTPUT);
    pinMode(SDCARD_CS, OUTPUT);

    if (!SD.begin(SDCARD_CS)) {
        Serial.println("sd init failed!");
        return;
    }
    Serial.println("sd init success");
    auto root = SD.open("/");
    root.seek(0);
    // root.rewindDirectory();
    File e = root.openNextFile();
    if (e) {
        Serial.println(e.name());
    } else {
        Serial.println("no file?");
    }
    e.close();
}

void setup()
{
    cli();

#ifdef SERIAL_DEBUG
    Serial.begin(38400);
    Serial.println("Hello ym2612");
#endif

    // initialize ym2612s
    start_clock();
    ym2612.setup();
    ym2612.reset();


    // initialize storage 
    test_sdcard();

    internal_storage.scanPatches();
    for (auto i=0; i < INTERNAL_PATCH_MAX_COUNT; i++) {
        if (internal_storage.patch_names[i][0] != 0) {
            Serial.print("found internal patch #");
            Serial.print(i);
            Serial.print(": [");
            Serial.print(internal_storage.patch_names[i]);
            Serial.println("]");
        }
    }

    //initialize all voices with sega doc patch
    for (int i=0; i < 6; i++) {
        ym2612.grandPianoVoice(i);
        ym2612.setOutputs(i, 3);
    }


    // initialize voices
    struct ym2612_patch_t p;
    memset(&p, 0, sizeof(p));

    struct ym2612_patch_t dumped;
    memset(&dumped, 0, sizeof(dumped));

    if (internal_storage.patch_names[0][0] != 0) {  
        internal_storage.readPatch(0, &p);

        // initial all voices with saved voice #0
        for (int i=0; i < 6; i++) {
            ym2612.applyPatch(i, &p);
        }

        Serial.println("voice loaded from patch #0");
    } else {

        // dump sega patch to internal patch #0
        ym2612.dumpPatch(0, &p);
        internal_storage.writePatch(0, &p);
        Serial.print(p.name);
        Serial.println(": saved to #0");

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

    //initialize TFT display
    setup_screen();

    // must occur after setup_gpio() and setup_screen()
    UiScreen::setActiveScreen(&splash_screen);


    //enable interrupts
    sei();
}



