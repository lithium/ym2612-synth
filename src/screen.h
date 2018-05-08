#ifndef SCREEN_H
#define SCREEN_H

#include "UiScreen.h"
#include "screen/DemoScreen.h"

#include <SPI.h>
#include <Wire.h>
#include <ILI9341_t3.h>

extern ILI9341_t3 tft;

extern UiScreen *active_screen;

extern DemoScreen demo_screen;

void setup_screen();
void set_active_screen(UiScreen *screen);

#endif