#ifndef DEMO_SCREEN_H
#define DEMO_SCREEN_H

#include "UiScreen.h"

class DemoScreen : public UiScreen
{
public:
    void encoderTurned(int direction, GpioEncoder *e) override;

    void paint();


private:
    int counters[8];
};

#endif
