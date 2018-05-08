#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "config.h"
#include "Encoder.h"
#include "Widget.h"

class UiScreen : 
        public Widget,
        public GpioEncoder::Listener
{
public:
    UiScreen();

private:

};



#endif
