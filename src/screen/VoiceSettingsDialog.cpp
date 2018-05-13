#include "VoiceSettingsDialog.h"

#include "screen.h"



static auto dialog_margin = 30;

static auto dialog_radius = 3;
static auto dialog_background = ILI9341_BLUE;
static auto dialog_border_color = ILI9341_WHITE;
static auto dialog_width = SCREEN_WIDTH-dialog_margin*2; 
static auto dialog_height = SCREEN_HEIGHT-dialog_margin*2; 
static auto active_border_color = ILI9341_WHITE;


static auto border_padding = 2;

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
    tft.fillRoundRect(dialog_margin,dialog_margin, dialog_width,dialog_height, dialog_radius, dialog_background);
    tft.drawRoundRect(dialog_margin+border_padding,dialog_margin+border_padding, dialog_width-border_padding*2,dialog_height-border_padding*2, dialog_radius, dialog_border_color);

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

}

void VoiceSettingsDialog::buttonPressed(Button *b)
{
    switch (b->number) {
        case 0:
            UiScreen::setActiveScreen(&main_screen);
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

    if (new_algorithm != last_algorithm) {
        if (last_algorithm != -1) {
            algorithmWidgets[last_algorithm].setActive(false);
        }
        algorithmWidgets[new_algorithm].setActive(true);
        last_algorithm = new_algorithm;
        repaint();
    }

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
        tft.drawRect(x, y, w, h, active_border_color);
    }
}    
