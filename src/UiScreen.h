#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "config.h"
#include "Encoder.h"
#include "Button.h"
#include "Widget.h"
#include "TouchScreen.h"

class UiScreen : 
        public Widget,
        public GpioEncoder::Listener,
        public Button::Listener,
        public TouchScreen::Listener
{
public:
    UiScreen();

    void encoderTurned(int direction, GpioEncoder *e) override;
    void buttonPressed(Button *b) override;
    void screenTouched(TS_Point p) override;


    virtual void loop(); // called in master loop() when active screen
    virtual void start(); // called when becoming active screen
    virtual void stop();  // called when active and another screen is becoming active

private:

};



#endif
