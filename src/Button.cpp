#include "Button.h"

static int _next_button_number = 0;

Button::Button()
{
}

void Button::setup(int pin, int debounce_threshold, int number)
{
    this->pin = pin;
    this->threshold = debounce_threshold;
    this->number = number;

    if (this->number == -1) {
        this->number = _next_button_number++;
    }

    pinMode(this->pin, INPUT_PULLUP);
}

void Button::setListener( Button::Listener *listener)
{
    this->listener = listener;
}

void Button::firePending()
{
    if (_pending) {
        if (listener) {
            listener->buttonPressed(this);
        }

        _pending = false;
    }
}


// Called in an ISR!
void Button::tick()
{
    if (_pending)
        return;

    bool v = digitalReadFast(this->pin);
    if (v == 0) {
        _counter += 1;
        if (_counter >= threshold) {
            _pending = true;
            _counter = 0;
        }
    } else {
        _counter = 0;
    }
}