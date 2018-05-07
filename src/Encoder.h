#ifndef ENCODER_H
#define ENCODER_H

#include <inttypes.h>
#include "gpio.h"



class GpioEncoder 
{
public:
    GpioEncoder(int gpio_pin_a, int gpio_pin_b);

    // returns: 1 clockwise, -1 counterclockwise, 0 ignore
    int8_t read(uint16_t state);
    void handle(uint16_t state);

    virtual void handleClockwise();
    virtual void handleAntiClockwise();

private:
    int pin_a, pin_b;
    uint8_t old_ab;

    int _detent_divider = 0;
    uint8_t _pulses_per_detent = 4;
    uint8_t _first = 0;
    uint8_t _first_to_skip = 2;
};




class TotalLevelEncoder : public GpioEncoder
{
public:
    TotalLevelEncoder(int gpio_pin_a, int gpio_pin_b);
    void handleClockwise() override;
    void handleAntiClockwise() override;
};

class SustainLevelEncoder : public GpioEncoder
{
public:
    SustainLevelEncoder(int gpio_pin_a, int gpio_pin_b);
    void handleClockwise() override;
    void handleAntiClockwise() override;
};
#endif