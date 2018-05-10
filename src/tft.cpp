#include "tft.h"


ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

void setup_screen()
{
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLUE);
}
