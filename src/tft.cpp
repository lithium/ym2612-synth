#include "tft.h"


ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

void setup_screen()
{
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLUE);
}

void emboss_frame(int x, int y, int w, int h, const uint16_t colors[4])
{
    tft.drawFastHLine(x,y, w, colors[0]);
    tft.drawFastVLine(x,y, h, colors[0]);

    tft.drawFastHLine(x+1,y+1, w-2, colors[1]);
    tft.drawFastVLine(x+1,y+1, h-2, colors[1]);

    tft.drawFastHLine(x+1,y+h-1, w-2, colors[2]);
    tft.drawFastVLine(x+w-1,y+1, h-2, colors[2]);

    tft.drawFastHLine(x,y+h, w, colors[3]);
    tft.drawFastVLine(x+w,y, h, colors[3]);
}

void draw_icon(int x, int y, int icon_number)
{
   const struct icon_t ico = ICONS[icon_number];
   tft.writeRect8BPP(x, y, ico.width, ico.height, ico.icon, icon_palette);
}
void erase_icon(int x, int y, int icon_number, int color)
{
   const struct icon_t ico = ICONS[icon_number];
   tft.fillRect(x, y, ico.width, ico.height, color);
}
