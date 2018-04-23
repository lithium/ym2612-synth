#include "ym2612.h"
#include "config.h"

Ym2612 ym2612(
    YM_CLK, 
    YM_D0, YM_D1, YM_D2, YM_D3, YM_D4, YM_D5, YM_D6, YM_D7,
    YM_IC, YM_CS, YM_RD, YM_WR, YM_A0, YM_A1
);

Ym2612::Ym2612(
    uint8_t clk,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t ic, uint8_t cs, uint8_t rd, uint8_t rw, uint8_t a0, uint8_t a1
)
{
    this->pin_clk = clk;
    this->pin_data[0] = d0;
    this->pin_data[1] = d1;
    this->pin_data[2] = d2;
    this->pin_data[3] = d3;
    this->pin_data[4] = d4;
    this->pin_data[5] = d5;
    this->pin_data[6] = d6;
    this->pin_data[7] = d7;
    this->pin_ic = ic;
    this->pin_cs = cs;
    this->pin_rd = rd;
    this->pin_rw = rw;
    this->pin_a0 = a0;
    this->pin_a1 = a1;
}

void Ym2612::setup()
{
    for (int i=0; i < 8; i++) {
        pinMode(this->pin_data[i], OUTPUT);
    }
    pinMode(this->pin_clk, OUTPUT);
    pinMode(this->pin_ic, OUTPUT);
    pinMode(this->pin_cs, OUTPUT);
    pinMode(this->pin_rd, OUTPUT);
    pinMode(this->pin_rw, OUTPUT);
    pinMode(this->pin_a0, OUTPUT);
    pinMode(this->pin_a1, OUTPUT);
}

void Ym2612::writeData(uint8_t b) 
{
    for (int i=0; i < 8; i++) {
        digitalWriteFast(this->pin_data[i], (b >> i) & 1);
    }
}
