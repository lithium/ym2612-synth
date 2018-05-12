#ifndef TFT_H
#define TFT_H

#include "config.h"
#include "icons.h"

#include <SPI.h>
#include <Wire.h>
#include <ILI9341_t3.h>

extern ILI9341_t3 tft;


void setup_screen();


void emboss_frame(int x, int y, int w, int h, const uint16_t colors[4]);
void draw_icon(int x, int y, int icon_number);
void erase_icon(int x, int y, int icon_number, int color);

#endif