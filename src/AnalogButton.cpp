#include "AnalogButton.h"


bool AnalogButton::readValue()
{
    auto v = analogRead(this->pin);
    // Serial.println(v);
    return v > 20;
    // return v != 0;
}
