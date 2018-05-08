#ifndef DEMO_SCREEN_H
#define DEMO_SCREEN_H

#include "UiScreen.h"
#include "Widget.h"


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

    void paint();
    void repaint();

private:
    DemoWidget widgets[8];
};

#endif
