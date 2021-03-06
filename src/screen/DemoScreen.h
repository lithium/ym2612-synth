#ifndef DEMO_SCREEN_H
#define DEMO_SCREEN_H

#include "UiScreen.h"
#include "Widget.h"
#include "gpio.h"
#include "tft.h"


class DemoWidget : public Widget
{
public:
    void paint() override;
    int counter;
};


class DemoScreen : public UiScreen
{
public:
    DemoScreen();
    
    void encoderTurned(int direction, GpioEncoder *e) override;
    void buttonPressed(Button *b) override;
    void screenTouched(TS_Point p) override;

    void paint() override;

private:
};

#endif
