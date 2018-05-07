
#include "DemoScreen.h"
#include "gpio.h"
#include "screen.h"


void DemoScreen::paint()
{
    Serial.println("paint it red");
    tft.fillScreen(ILI9341_RED);
}

void DemoScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    int enc = get_encoder_number(e) + 1;
    Serial.print("encoder #");
    Serial.print(enc);
    Serial.print(" turned ");
    Serial.println(direction == 1 ? "right" : "left");
}

