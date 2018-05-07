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
};




class TotalLevelEncoder : public GpioEncoder
{
public:
    TotalLevelEncoder(int gpio_pin_a, int gpio_pin_b);
    void handleClockwise() override;
    void handleAntiClockwise() override;
};

#endif