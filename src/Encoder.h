#ifndef ENCODER_H
#define ENCODER_H

#include "config.h"



class GpioEncoder 
{
public:
    GpioEncoder();

    void setup(int gpio_pin_a, int gpio_pin_b, int pulses_per_detent=4, int first_to_skip=0);

    // returns: 1 clockwise, -1 counterclockwise, 0 ignore
    int8_t read(uint16_t state);
    void handle(uint16_t state);


    class Listener {
    public:
        virtual void encoderTurned(int direction, GpioEncoder *encoder) = 0;
    };

    void setListener(Listener *listener);

    uint8_t _pulses_per_detent = 4;
private:
    int pin_a, pin_b;
    uint8_t old_ab;

    int _detent_divider = 0;
    uint8_t _first = 0;
    uint8_t _first_to_skip = 2;

    Listener *listener = NULL;
};



#endif