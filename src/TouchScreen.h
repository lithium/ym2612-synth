#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "config.h"
#include <XPT2046_Touchscreen.h>


class TouchScreen
{
public:
    TouchScreen(int cs_pin = TOUCH_CS);

    void setup(int cs_pin);

    class Listener {
    public:
        virtual void screenTouched(TS_Point position) = 0;
    };

    void setListener(Listener *listener) { this->listener = listener; }

    void notifyListener(TS_Point p) {
        if (listener) {
        }
    }


    void check();

    int cs_pin;
private:
    XPT2046_Touchscreen tsc2046;
    TS_Point _last_touch;

    Listener *listener = nullptr;
};

extern TouchScreen touchscreen;

#endif
