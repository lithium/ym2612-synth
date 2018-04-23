#ifndef YM2612_H
#define YM2612_h

#include "config.h"



class Ym2612 {
public:
    Ym2612(
        uint8_t clk,
        uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
        uint8_t ic, uint8_t cs, uint8_t rd, uint8_t rw, uint8_t a0, uint8_t a1
    );
    void setup();

    void writeData(uint8_t b);

private:
    uint8_t pin_clk;
    uint8_t pin_data[8];
    uint8_t pin_ic;
    uint8_t pin_cs;
    uint8_t pin_rd;
    uint8_t pin_rw;
    uint8_t pin_a0;
    uint8_t pin_a1;
};


extern Ym2612 ym2612;


#endif