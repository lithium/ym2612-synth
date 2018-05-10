#ifndef TFT_H
#define TFT_H

#include "config.h"

#include <SPI.h>
#include <Wire.h>
#include <ILI9341_t3.h>

extern ILI9341_t3 tft;


void setup_screen();

#endif