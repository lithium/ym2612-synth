#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "config.h"
#include "encoder.h"

class UiScreen : public GpioEncoder::Listener
{
public:
    UiScreen();


    void encoderTurned(int direction, GpioEncoder *e) override;

private:

};

#endif
