
#include "DemoScreen.h"
#include "gpio.h"

void DemoScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    int enc = get_encoder_number(e) + 1;
    Serial.print("encoder #");
    Serial.print(enc);
    Serial.print(" turned ");
    Serial.println(direction == 1 ? "right" : "left");
}
