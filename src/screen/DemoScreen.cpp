
#include "DemoScreen.h"
#include "gpio.h"
#include "screen.h"


void DemoScreen::paint()
{
    Serial.println("paint it ");
    tft.fillScreen(ILI9341_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);

    auto x = 20;
    auto y = 20;

    for (int i=0; i < 8; i++) {
        tft.setCursor(x,y);
        tft.print("ENC #");
        tft.print(i+1);
        tft.print(": ");
        tft.print(counters[i]);
        y += 20;
    }
}

void DemoScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    int enc = get_encoder_number(e) + 1;
    Serial.print("encoder #");
    Serial.print(enc);
    Serial.print(" turned ");
    Serial.println(direction == 1 ? "right" : "left");

    counters[enc - 1] += direction;
    setDirty();
}

