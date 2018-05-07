#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "config.h"
#include "Encoder.h"

class UiScreen : public GpioEncoder::Listener
{
public:
    UiScreen();

    virtual void paint();

    bool isDirty();
    void setDirty(bool dirty = true);

private:

    bool _dirty = false;
};



#endif