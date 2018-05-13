#ifndef ANALOG_BUTTON_H
#define ANALOG_BUTTON_H

#include "config.h"
#include "Button.h"

class AnalogButton :
        public Button
{

    bool readValue() override;
};

#endif
