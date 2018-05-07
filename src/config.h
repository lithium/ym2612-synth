#ifndef CONFIG_H
#define CONFIG_H


#include <Arduino.h>


#define SERIAL_DEBUG




// ym2612 pin assignments
#define YM_D0 0
#define YM_D1 1
#define YM_D2 2
#define YM_D3 3
#define YM_D4 4
#define YM_D5 5
#define YM_D6 6
#define YM_D7 7

#define YM_CS 14
#define YM2_CS 15
#define YM_WR 16
#define YM_RD 17
#define YM_A0 20
#define YM_A1 21
#define YM_CLK 22
#define YM_IC 23


// tft pin assignments
#define TFT_CS 10
#define TFT_DC 9

// touch controller
#define TOUCH_CS 8
#define TOUCH_IRQ 19

// io expand assignments
#define IO_CS 18
#define IO_IRQ A14


// encoder switches
#define ENC1_SW A11
#define ENC5_SW A10


// builtin led
#define PIN_LED 13


#endif