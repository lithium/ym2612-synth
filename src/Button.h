#ifndef BUTTON_H
#define BUTTON_H

#include "config.h"


class Button
{
public:
    Button();

    void setup(int pin, int debounce_threshold=50, int number=-1);

    class Listener {
    public:
        virtual void buttonPressed(Button *b) = 0;
    };

    void setListener(Listener *listener);

    void tick(); // called in ISR!
    void firePending(); // calls listener if debounced click is pending


    // public members
    int number;         // user definable button "number"
    int pin;
    int threshold;

private:
    int _counter = 0;
    bool _pending = false;
    bool _sent = false;


    Listener *listener = nullptr;
};


#endif