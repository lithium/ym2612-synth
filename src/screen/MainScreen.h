#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "UiScreen.h"
#include "widgets/OperatorWidget.h"
#include "tft.h"


#define OPERATOR_COUNT 4

class MainScreen : public UiScreen
{
public:
    MainScreen();

    void paint() override;

    void screenTouched(TS_Point p) override;

private:
    OperatorWidget ops[4];

    OperatorWidget *active_op = nullptr;
};

#endif