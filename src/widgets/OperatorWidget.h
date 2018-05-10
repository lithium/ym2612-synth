#ifndef OPERATOR_WIDGET_H
#define OPERATOR_WIDGET_H

#include "config.h"
#include "Widget.h"
#include "tft.h"

class OperatorWidget : public Widget
{
public:
    OperatorWidget(int op_number=0);

    void paint() override; 

    void setActive(bool active);

    int op_number;

private:
    bool _active = false;


};


#endif