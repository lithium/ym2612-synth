#include "Encoder.h"

static int8_t _encoder_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

inline bool read_pin(uint16_t port, uint8_t pin)
{
    return (port & (1<<pin)) == (1<<pin);
}


GpioEncoder::GpioEncoder()
{
    pin_a = pin_b = -1;
}

void GpioEncoder::setup(int gpio_pin_a, int gpio_pin_b, int pulses_per_detent, int first_to_skip)
{
    pin_a = gpio_pin_a;
    pin_b = gpio_pin_b;
    old_ab = 0;
    _detent_divider = 0;
    _pulses_per_detent = pulses_per_detent;
    _first = 0;
    _first_to_skip = first_to_skip;
    listener = NULL;
}


int8_t GpioEncoder::read(uint16_t debounced_state)
{
    old_ab <<= 2;
    old_ab |= read_pin(debounced_state, pin_a) << 1;
    old_ab |= read_pin(debounced_state, pin_b);
    if (_first < _first_to_skip) {
        // hack to skip first couple to align with detents
        _first++;
        return 0;
    }
    return _encoder_states[(old_ab & 0x0f)];
}

void GpioEncoder::handle(uint16_t debounced_state)
{
    int val = read(debounced_state);
    if (val != 0) {
        _detent_divider += val;
        if (abs(_detent_divider) == _pulses_per_detent) {
            if (this->listener) {
                this->listener->encoderTurned(val, this);
            }

            _detent_divider = 0;
        }
    }
}

void GpioEncoder::setListener(GpioEncoder::Listener *listener)
{
    this->listener = listener;
}

