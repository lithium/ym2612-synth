#include "TouchScreen.h"


TouchScreen touchscreen;


TouchScreen::TouchScreen(int cs_pin) : tsc2046(cs_pin), _last_touch(-1,-1,-1)
{
    setup(cs_pin);
}

void TouchScreen::setup(int cs_pin)
{
    this->cs_pin = cs_pin; 
}



void TouchScreen::check() 
{
    if (!listener) 
        return;

    if (tsc2046.touched()) {
        TS_Point p = tsc2046.getPoint();
        if (p != _last_touch) {
            notifyListener(p);
            Serial.print("touched! ");
            Serial.print(p.x);
            Serial.print(", ");
            Serial.println(p.y);
            _last_touch = p;
        }
    }
}
