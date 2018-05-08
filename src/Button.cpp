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
    if (_pending && !_sent) {
        if (listener) {
            listener->buttonPressed(this);
        }
        _sent = true;
        _pending = false;
    }
}


// Called in an ISR!
void Button::tick()
{
    bool v = digitalReadFast(this->pin);

    if (v == 0) {
        if (_counter < threshold) {
            _counter += 1;
        } else if (!_sent) {
            _pending = true;
            _sent = false;
        }
    } else {
        _counter = 0;
        _pending = false;
        _sent = false;
    }
}