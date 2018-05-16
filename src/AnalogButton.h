#ifndef ANALOG_BUTTON_H
#define ANALOG_BUTTON_H

#include "config.h"
#include "Button.h"

class AnalogButton :
        public Button
{
public:

    void setRange(int min, int max);
    bool readValue() override;

private:
    int min=20;
    int max=4096;
};

#endif
