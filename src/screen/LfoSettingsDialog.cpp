#include "LfoSettingsDialog.h"
#include "screen.h"


static auto padding = 4;
static auto _left = dialog_margin + border_padding;
static auto _top = dialog_margin + border_padding;
static const auto label_width = 40;

static const char *_frequency_values[] = {
    "3.98",
    "5.56",  
    "6.02",
    "6.37",
    "6.88",
    "9.63",
    "48.1",
    "72.2",
};

static const char *_am_depth_values[] = {
    "0",
    "1.4",
    "5.9",
    "11.8",
};

static const char *_fm_depth_values[] = {
    "0",
    "3.4",
    "6.7",
    "10",
    "14",
    "20",
    "40",
    "80"
};
static const char *_op_names[] = {
    "OP1",
    "OP2",
    "OP3",
    "OP4",
};

LfoSettingsDialog::LfoSettingsDialog() : 
    lfoFrequencyLabel(nullptr, ComicSansMS_14, COLOR_white, COLOR_dialog_background),
    amDepthLabel(nullptr, ComicSansMS_14, COLOR_white, COLOR_dialog_background),
    fmDepthLabel(nullptr, ComicSansMS_14, COLOR_white, COLOR_dialog_background)
{


    auto l = _left + padding;
    auto t = _top + padding;

    // enabled 
    lfoEnabledButton.setBounds(l, t, 90, 40);
    lfoEnabledButton.padding_top = 12;
    lfoEnabledButton.padding_left = 8;
    lfoEnabledButton.setLabel("Disabled");
    addWidget(&lfoEnabledButton);


    // frequency
    l += 100 + label_width + 10;
    lfoFrequencyLabel.setBounds(l, t, 90, 20);
    addWidget(&lfoFrequencyLabel);


    // am/fm depth
    l = _left + padding + label_width;
    t = _top + padding + 60;

    amDepthLabel.setBounds(l, t, 90, 20);
    addWidget(&amDepthLabel);

    t += 40;
    fmDepthLabel.setBounds(l, t, 90, 20);
    addWidget(&fmDepthLabel);


    // am operator enabled 
    const auto button_size = 60;
    const auto button_padding = 10;
    // l = _left + padding + button_padding;
    t = _top + padding + 30;
    l = 145;

    const int button_pos[][2] = {
        {l, t},
        {l+button_size+button_padding, t},
        {l, t+button_size+button_padding},
        {l+button_size+button_padding, t+button_size+button_padding},
    };
    for (auto i=0; i < 4; i++) {
        amEnabledButtons[i].setBounds(button_pos[i][0], button_pos[i][1], button_size, button_size);
        amEnabledButtons[i].setLabel(_op_names[i]);
        amEnabledButtons[i].padding_top = 20;
        amEnabledButtons[i].padding_left = 12;
        addWidget(&amEnabledButtons[i]);
        l += button_size + padding;
    }
}

void LfoSettingsDialog::paint()
{
    DialogScreen::paint();

    auto l = _left + padding;
    auto t = _top + padding + 60;
    tft.setCursor(l, t);
    tft.print("AM:");
    tft.setCursor(l+75, t);
    tft.print("dB");

    t += 40; 
    tft.setCursor(l, t);
    tft.print("FM:");
    tft.setCursor(l+68, t);
    tft.print("c");

    l = _left + padding + 100;
    t = _top +padding;
    tft.setCursor(l, t);
    tft.print("Rate:");
    tft.setCursor(l+90, t);
    tft.print("Hz");

    settingsChanged(nullptr,-1,-1);
    setDirty();
    repaint();
}


void LfoSettingsDialog::encoderTurned(int direction, GpioEncoder *e)
{
    int enc = get_encoder_number(e);
    SynthVoice *voice = synth.getActiveVoice();

    switch (enc)
    {
        case 0: {
            int am = voice->getLfoAm();
            if (am+direction < 0 || am+direction > 3) {
                return;
            }
            voice->setLfoAm(am+direction);
            break;
        }
        case 1: {
            int fm = voice->getLfoFm();
            if (fm+direction < 0 || fm+direction > 7) {
                return;
            }
            voice->setLfoFm(fm+direction);
            break;
        }
        case 7: {
            int f = voice->getLfoFrequency();
            if (f+direction < 0 || f+direction > 7) {
                return;
            }
            voice->setLfoFrequency(f+direction);
            break;
        }
    }

}
void LfoSettingsDialog::buttonPressed(Button *b)
{
    switch (b->number) {
        case 0:
            UiScreen::setActiveScreen(&voice_settings_dialog);
            break;
        case 1:
            UiScreen::setActiveScreen(&main_screen);
            break;
        case 2:
            UiScreen::setActiveScreen(&patch_dialog);
            break;
    }

}
void LfoSettingsDialog::screenTouched(TS_Point p)
{
    SynthVoice *voice = synth.getActiveVoice();
    Widget *w = getChildAtPoint(p);

    if (w == &lfoEnabledButton) {
        voice->enableLfo(!lfoEnabledButton.isActive());
        repaint();
    }
    else {
        for (auto i=0; i < 4; i++) {
            if (w == &amEnabledButtons[i]) {
                voice->enableLfoForOperator(i, !amEnabledButtons[i].isActive());
                break;
            }
        }
        repaint();
    }
}

void LfoSettingsDialog::settingsChanged(Ym2612 *ym, uint8_t chan, uint8_t oper)
{
    SynthVoice *voice = synth.getActiveVoice();

    auto enabled = voice->getLfoEnabled();
    if (enabled != lfoEnabledButton.isActive()) {
        lfoEnabledButton.setActive(enabled);
        lfoEnabledButton.setLabel(enabled ? "Enabled" : "Disabled");
    }

    auto new_freq = _frequency_values[voice->getLfoFrequency()];
    if(new_freq != lfoFrequencyLabel.getLabel()) {
        lfoFrequencyLabel.setLabel(new_freq);
    }

    auto new_am = _am_depth_values[voice->getLfoAm()];
    if (new_am != amDepthLabel.getLabel()) {
        amDepthLabel.setLabel(new_am);
    }

    auto new_fm = _fm_depth_values[voice->getLfoFm()];
    if (new_fm != fmDepthLabel.getLabel()) {
        fmDepthLabel.setLabel(new_fm);
    }

    for (auto i=0; i < 4; i++) {
        amEnabledButtons[i].setActive(voice->getLfoEnabledForOperator(i));
    }

    repaint();
}
