#ifndef OPERATOR_WIDGET_H
#define OPERATOR_WIDGET_H

#include "config.h"
#include "Widget.h"
#include "tft.h"
#include "ym2612.h"
#include "patch.h"

class OperatorWidget : public Widget
{
public:
    OperatorWidget(int op_number=0);

    void paint() override; 
    void paintMultiplier(uint8_t multiplier, int color);
    void paintDetune(uint8_t detune, int color);

    void setActive(bool active);
    void operatorChanged(struct ym2612_patch_op_t new_patch_op);

    int op_number;

private:
    bool _active = false;


    struct ym2612_patch_op_t last_patch;
};


#endif