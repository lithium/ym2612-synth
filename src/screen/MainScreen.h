#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "UiScreen.h"
#include "widgets/OperatorWidget.h"
#include "tft.h"
#include "ym2612.h"


#define OPERATOR_COUNT 4

class MainScreen : public UiScreen
{
public:
    MainScreen();

    void paint() override;
    void paintAlgorithm(uint8_t algorithm, bool erase=false);
    void paintFeedback(uint8_t feedback, bool erase=false);

    void paintPatchName(char *name, bool erase=false);

    void start() override;
    void stop() override;

    void screenTouched(TS_Point p) override;
    void encoderTurned(int direction, GpioEncoder *e) override;
    void buttonPressed(Button *b) override;

    void settingsChanged(uint8_t chan, uint8_t oper) override;

private:
    OperatorWidget ops[4];

    OperatorWidget *active_op = nullptr;

    int active_channel = 0;
    
    struct ym2612_patch_t last_patch;
};

#endif