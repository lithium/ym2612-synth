#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "config.h"
#include <XPT2046_Touchscreen.h>


class TouchScreen
{
public:
    TouchScreen(int cs_pin=TOUCH_CS, int debounce_threshold=00);

    void setup(int cs_pin, int debounce_threshold);

    class Listener {
    public:
        virtual void screenTouched(TS_Point position) = 0;
        virtual void screenReleased() {}
    };

    void setListener(Listener *listener) { this->listener = listener; }

    void notifyListener(TS_Point p) {
        if (listener) {
            listener->screenTouched(p);
        }
    }


    void check();

    int cs_pin;
    int threshold;
private:
    XPT2046_Touchscreen tsc2046;
    TS_Point _last_touch;
    bool _pointer_down = false;

    Listener *listener = nullptr;
};

extern TouchScreen touchscreen;

#endif
