#ifndef LFO_SETTINGS_DIALOG_H
#define LFO_SETTINGS_DIALOG_H

#include "config.h"
#include "DialogScreen.h"
#include "tft.h"
#include "ym2612.h"


class LfoSettingsDialog : public DialogScreen
{
public:
    LfoSettingsDialog();

    void paint() override;

    void encoderTurned(int direction, GpioEncoder *e) override;
    void buttonPressed(Button *b) override;
    void screenTouched(TS_Point p) override;
    void settingsChanged(uint8_t chan, uint8_t oper) override;

private:
    
};

#endif
