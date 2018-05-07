#include "Encoder.h"

static int8_t _encoder_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

inline bool read_pin(uint16_t port, uint8_t pin)
{
    return (port & (1<<pin)) == (1<<pin);
}


GpioEncoder::GpioEncoder(int gpio_pin_a, int gpio_pin_b)
{
    pin_a = gpio_pin_a;
    pin_b = gpio_pin_b;
    old_ab = 0;
}


int8_t GpioEncoder::read(uint16_t debounced_state)
{
    old_ab <<= 2;
    old_ab |= read_pin(debounced_state, pin_a) << 1;
    old_ab |= read_pin(debounced_state, pin_b);
    return _encoder_states[(old_ab & 0x0f)];
}

void GpioEncoder::handle(uint16_t debounced_state)
{
    int val = read(debounced_state);
    if (val == -1) {
        handleAntiClockwise();
    } 
    else if (val == 1) {
        handleClockwise();
    }
}

void GpioEncoder::handleClockwise()
{
    Serial.println("super clockwise");

}
void GpioEncoder::handleAntiClockwise()
{

    Serial.println("super anti clockwise");
}


// === tl encoder
TotalLevelEncoder::TotalLevelEncoder(int gpio_pin_a, int gpio_pin_b) : GpioEncoder(gpio_pin_a, gpio_pin_b)
{
}

void TotalLevelEncoder::handleClockwise()
{
    Serial.println("tl clockwise");
}

void TotalLevelEncoder::handleAntiClockwise()
{
    Serial.println("tl anti clockwise");
}
