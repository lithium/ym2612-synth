#include "VoiceSettingsDialog.h"

#include "screen.h"



static auto dialog_margin = 30;

static auto dialog_radius = 3;
static auto dialog_background = ILI9341_BLUE;
static auto dialog_border_color = ILI9341_WHITE;
static auto dialog_width = SCREEN_WIDTH-dialog_margin*2; 
static auto dialog_height = SCREEN_HEIGHT-dialog_margin*2; 

VoiceSettingsDialog::VoiceSettingsDialog()
{

}


void VoiceSettingsDialog::paint()
{
    auto border_padding = 3;

    // dont clear because we're an overlay dialog
    tft.fillRoundRect(dialog_margin,dialog_margin, dialog_width,dialog_height, dialog_radius, dialog_background);
    tft.drawRoundRect(dialog_margin+border_padding,dialog_margin+border_padding, dialog_width-border_padding*2,dialog_height-border_padding*2, dialog_radius, dialog_border_color);

}
void VoiceSettingsDialog::start()
{
    ym2612.setListener(this);
}
void VoiceSettingsDialog::stop()
{
    // ym2612.removeListener(this);
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

void VoiceSettingsDialog::settingsChanged(uint8_t chan, uint8_t oper)
{

}
