#ifndef TOGGLE_BUTTON_H
#define TOGGLE_BUTTON_H

#include "config.h"
#include "Label.h"
#include "colors.h"


class ToggleButton : public Label
{
public:

    void paint() override;
    void setActive(bool active = true) {
        _active = active;
        setDirty(true);
    }
    bool isActive() { return _active; }

private:
    bool _active = false;

};


#endif
