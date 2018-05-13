#ifndef VOICE_SETTINGS_DIALOG_H
#define VOICE_SETTINGS_DIALOG_H

#include "config.h"
#include "DialogScreen.h"
#include "tft.h"
#include "ym2612.h"


class AlgorithmWidget : 
        public Widget
{
public:
    AlgorithmWidget(int algorithm_number=-1);

    void paint() override;

    void setActive(bool active) {
        this->active = active;
        setDirty(true);
    }

    uint8_t number;
    bool active = false;
private:
};

class VoiceSettingsDialog :
        public DialogScreen
{
public:
    VoiceSettingsDialog();


    void paint() override;
    void paintFeedback(uint8_t feedback, bool erase);

    void start() override;
    void stop() override;


    void encoderTurned(int direction, GpioEncoder *e) override;
    void buttonPressed(Button *b) override;
    void screenTouched(TS_Point p) override;

    void settingsChanged(uint8_t chan, uint8_t oper) override;

private:
    uint8_t last_algorithm = -1;
    uint8_t last_feedback = -1;
    uint8_t current_channel = 0;

    AlgorithmWidget algorithmWidgets[8];
    AlgorithmWidget *activeWidget = nullptr;
};

#endif
