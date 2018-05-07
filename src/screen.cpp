#include "screen.h" 
#include "gpio.h"



Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

DemoScreen demo_screen;
UiScreen *active_screen = NULL;


void set_active_screen(UiScreen *screen)
{
    active_screen = screen;
    for (int i=0; i < ENCODER_COUNT; i++) {
        encoders[i].setListener(active_screen);
    }
    if (active_screen) {
        active_screen->setDirty();
    }
}


void setup_screen()
{
    tft.begin();
    tft.fillScreen(ILI9341_BLUE);
}