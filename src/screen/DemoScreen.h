#ifndef DEMO_SCREEN_H
#define DEMO_SCREEN_H

#include "UiScreen.h"

class DemoScreen : public UiScreen
{
    void encoderTurned(int direction, GpioEncoder *e) override;
};

#endif
