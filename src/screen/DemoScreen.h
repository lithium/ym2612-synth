#ifndef DEMO_SCREEN_H
#define DEMO_SCREEN_H

#include "UiScreen.h"
#include "Widget.h"
#include <LinkedList.h>


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


    void addWidget(Widget *w);

private:
    // DemoWidget widgets[8];
    LinkedList<Widget *> widgets;
};

#endif
