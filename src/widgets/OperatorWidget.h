#ifndef OPERATOR_WIDGET_H
#define OPERATOR_WIDGET_H

#include "config.h"
#include "Widget.h"
#include "tft.h"

class OperatorWidget : public Widget
{
public:
    OperatorWidget();

    void paint() override; 

    void setActive(bool active) { _active = active; }

private:
    bool _active = false;
};


#endif