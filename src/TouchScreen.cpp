#include "TouchScreen.h"


TouchScreen touchscreen;


TouchScreen::TouchScreen(int cs_pin, int debounce_threshold) : tsc2046(cs_pin), _last_touch(-1,-1,-1)
{
    setup(cs_pin, debounce_threshold);
}

void TouchScreen::setup(int cs_pin, int debounce_threshold)
{
    this->cs_pin = cs_pin; 
    this->threshold = debounce_threshold;
}



void TouchScreen::check() 
{
    if (!listener) 
        return;

    if (tsc2046.touched()) {
        TS_Point p = tsc2046.getPoint();
        if (!_pointer_down) {
            if ((abs(p.x - _last_touch.x) > threshold) ||
                (abs(p.y - _last_touch.y) > threshold)) {
                notifyListener(p);
                _last_touch = p;
            }
            _pointer_down = true;
        }
    } 
    else if (_pointer_down) {
        _pointer_down = false;
        if (listener) {
            listener->screenReleased();
        }
    }


}
