#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "config.h"
#include "Encoder.h"
#include "gpio.h"





class UiScreen : public GpioEncoder::Listener
{
public:
    UiScreen();


    void encoderTurned(int direction, GpioEncoder *e) override;

private:

};


extern UiScreen *active_screen;
extern UiScreen demo_screen;

void set_active_screen(UiScreen *screen);

#endif
