#ifndef VOICE_SETTINGS_DIALOG_H
#define VOICE_SETTINGS_DIALOG_H

#include "config.h"
#include "UiScreen.h"
#include "tft.h"
#include "ym2612.h"

class VoiceSettingsDialog :
        public UiScreen,
        public Ym2612::Listener
{
public:
    VoiceSettingsDialog();


    void paint() override;
    void start() override;
    void stop() override;


    void encoderTurned(int direction, GpioEncoder *e) override;
    void buttonPressed(Button *b) override;

    void settingsChanged(uint8_t chan, uint8_t oper) override;

private:
    struct ym2612_patch_t last_patch;
};

#endif
