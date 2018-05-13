#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "config.h"
#include "Encoder.h"
#include "Button.h"
#include "Widget.h"
#include "TouchScreen.h"
#include "gpio.h"
#include "ym2612.h"

class UiScreen : 
        public Widget,
        public GpioEncoder::Listener,
        public Button::Listener,
        public TouchScreen::Listener,
        public Ym2612::Listener
{
public:
    UiScreen();

    virtual void encoderTurned(int direction, GpioEncoder *e) override;
    virtual void buttonPressed(Button *b) override;
    virtual void screenTouched(TS_Point p) override;
    virtual void settingsChanged(uint8_t chan, uint8_t oper) override;


    virtual void loop(); // called in master loop() when active screen
    virtual void start(); // called when becoming active screen
    virtual void stop();  // called when active and another screen is becoming active


    static void setActiveScreen(UiScreen *s);
private:

};



extern UiScreen *active_screen;



#endif
