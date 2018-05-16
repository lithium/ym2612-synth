#include "AnalogButton.h"

void AnalogButton::setRange(int min, int max)
{
    this->min = min;
    this->max = max;
}

bool AnalogButton::readValue()
{
    auto v = analogRead(this->pin);
    return !((v >= min) && (v <= max)); // active low
}
