#include "VoiceSettingsDialog.h"

#include "screen.h"
#include <font_ComicSansMS.h>


VoiceSettingsDialog::VoiceSettingsDialog()
{
    auto padding = 3;
    auto top = dialog_margin + border_padding + padding + 20;
    auto left = dialog_margin + border_padding + padding-1;

    const auto icon_width = 60;
    const auto icon_height = 60;

    algorithmWidgets[0].number = ICON_algorithm0;
    algorithmWidgets[0].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;
    algorithmWidgets[1].number = ICON_algorithm1;
    algorithmWidgets[1].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;
    algorithmWidgets[2].number = ICON_algorithm2;
    algorithmWidgets[2].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;
    algorithmWidgets[3].number = ICON_algorithm3;
    algorithmWidgets[3].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;

    top += icon_height + padding;
    left = dialog_margin + border_padding + padding;

    algorithmWidgets[4].number = ICON_algorithm4;
    algorithmWidgets[4].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;
    algorithmWidgets[5].number = ICON_algorithm5;
    algorithmWidgets[5].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;
    algorithmWidgets[6].number = ICON_algorithm6;
    algorithmWidgets[6].setBounds(left, top, icon_width, icon_height);
    left += icon_width + padding;
    algorithmWidgets[7].number = ICON_algorithm7;
    algorithmWidgets[7].setBounds(left, top, icon_width, icon_height);

    for (int i=0; i <8; i++) {
        addWidget(&algorithmWidgets[i]);
    }

}


void VoiceSettingsDialog::paint()
{

    // dont clear because we're an overlay dialog
    tft.fillRoundRect(dialog_margin,dialog_margin, dialog_width,dialog_height, dialog_radius, COLOR_dialog_background);
    tft.drawRoundRect(dialog_margin+border_padding,dialog_margin+border_padding, dialog_width-border_padding*2,dialog_height-border_padding*2, dialog_radius, COLOR_dialog_border);

    settingsChanged(-1,-1);
    repaint();
}
void VoiceSettingsDialog::start()
{
    ym2612.addListener(this);
    for (int i=0; i < 8; i++) {
        algorithmWidgets[i].setDirty(true);
    }
}
void VoiceSettingsDialog::stop()
{
    ym2612.removeListener(this);
}


void VoiceSettingsDialog::encoderTurned(int direction, GpioEncoder *e)
{
    int enc = get_encoder_number(e);
    int chan = current_channel;
    switch (enc)
    {
        case 0: {
            auto feedback = ym2612.getFeedback(chan);
            if (feedback + direction < 0 || feedback+direction > 7) {
                return;
            }
            ym2612.setFeedback(chan, feedback + direction);
        }
    }
}

void VoiceSettingsDialog::buttonPressed(Button *b)
{
    switch (b->number) {
        case 0:
            UiScreen::setActiveScreen(&main_screen);
            break;
        case 1:
            UiScreen::setActiveScreen(&lfo_settings_dialog);
            break;
    }

}
void VoiceSettingsDialog::screenTouched(TS_Point p) 
{
    AlgorithmWidget *w = (AlgorithmWidget *)getChildAtPoint(p);
    if (!w || w->number == -1) {
        return;
    }

    ym2612.setAlgorithm(current_channel, w->number);
}

void VoiceSettingsDialog::settingsChanged(uint8_t chan, uint8_t oper)
{
    if (chan == 255) {
        chan = current_channel;
    }
    auto new_algorithm = ym2612.getAlgorithm(chan);
    auto new_feedback = ym2612.getFeedback(chan);

    if (new_algorithm != last_algorithm) {
        if (last_algorithm != -1) {
            algorithmWidgets[last_algorithm].setActive(false);
        }
        algorithmWidgets[new_algorithm].setActive(true);
        last_algorithm = new_algorithm;
        repaint();
    }
    if (new_feedback != last_feedback) {
        if (last_feedback != -1) {
            paintFeedback(last_feedback, true);
        }
        if (new_feedback != -1) {
            paintFeedback(new_feedback, false);
        }
        last_feedback = new_feedback;
    }

}
void VoiceSettingsDialog::paintFeedback(uint8_t feedback, bool erase)
{
    tft.setFont(ComicSansMS_14);
    tft.setCursor(15,9);
    tft.setTextColor(erase ? COLOR_black : COLOR_white);
    tft.print(feedback);
}


AlgorithmWidget::AlgorithmWidget(int algorithm_number) : number(algorithm_number)
{
}
void AlgorithmWidget::paint()
{
    if (number == -1) {
        return;
    }

    draw_algorithm_icon(x, y, this->number);
    if (active) {
        tft.drawRect(x, y, w, h, COLOR_active_border);
    }
}    
