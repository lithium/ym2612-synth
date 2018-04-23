#include "ym2612.h"
#include "config.h"

Ym2612 ym2612(
    YM_D0, YM_D1, YM_D2, YM_D3, YM_D4, YM_D5, YM_D6, YM_D7,
    YM_IC, YM_CS, YM_RD, YM_WR, YM_A0, YM_A1
);

Ym2612::Ym2612(
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t ic, uint8_t cs, uint8_t rd, uint8_t wr, uint8_t a0, uint8_t a1
)
{
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
    this->pin_wr = wr;
    this->pin_a0 = a0;
    this->pin_a1 = a1;

}

void Ym2612::setup()
{
    for (int i=0; i < 8; i++) {
        pinMode(this->pin_data[i], OUTPUT);
    }
    pinMode(this->pin_ic, OUTPUT);
    pinMode(this->pin_cs, OUTPUT);
    pinMode(this->pin_rd, OUTPUT);
    pinMode(this->pin_wr, OUTPUT);
    pinMode(this->pin_a0, OUTPUT);
    pinMode(this->pin_a1, OUTPUT);


    digitalWriteFast(this->pin_ic, HIGH);
    digitalWriteFast(this->pin_cs, HIGH);
    digitalWriteFast(this->pin_wr, HIGH);
    digitalWriteFast(this->pin_rd, HIGH);
    digitalWriteFast(this->pin_a0, LOW);
    digitalWriteFast(this->pin_a1, LOW);
}


void Ym2612::reset()
{
    digitalWriteFast(this->pin_ic, LOW);
    delay(10);
    digitalWriteFast(this->pin_ic, HIGH);
    delay(10);
}


void Ym2612::segaDocTestProgram()
{
    write_register(0x22, 0);          // lfo off
    write_register(0x27, 0);          // ch3 mode

    write_register(0x28, 0);          // all channels off
    write_register(0x28, 1);
    write_register(0x28, 2);          
    write_register(0x28, 4);          // 3 gets skipped!
    write_register(0x28, 5);
    write_register(0x28, 6);

    write_register(0x2B, 0);          // dac off

    write_register(0x30, 0x71);       // DT1/MUL
    write_register(0x34, 0x0D);
    write_register(0x38, 0x33);
    write_register(0x3C, 0x01);

    write_register(0x40, 0x23);       // Total Level
    write_register(0x44, 0x2D);
    write_register(0x48, 0x26);
    write_register(0x4C, 0x00);

    write_register(0x50, 0x5F);       // RS/AR 
    write_register(0x54, 0x99);
    write_register(0x58, 0x5F);
    write_register(0x5C, 0x94);

    write_register(0x60, 0x05);       // AM/D1R
    write_register(0x64, 0x05);
    write_register(0x68, 0x05);
    write_register(0x6C, 0x07);

    write_register(0x70, 0x02);       // D2R
    write_register(0x74, 0x02);
    write_register(0x78, 0x02);
    write_register(0x7C, 0x02);

    write_register(0x80, 0x11);       // D1L/RR
    write_register(0x84, 0x11);
    write_register(0x88, 0x11);
    write_register(0x8C, 0xA6);

    write_register(0x90, 0x00);       // Proprietary
    write_register(0x94, 0x00);
    write_register(0x98, 0x00);
    write_register(0x9C, 0x00);

    write_register(0xB0, 0x32);      // Feedback/algorithm
    write_register(0xB4, 0xC0);      // Both speakers on

    write_register(0x28, 0x00);      // Key off

    write_register(0xA4, 0x22);      // Set frequency
    write_register(0xA0, 0x69);

    write_register(0x28, 0xF0);      // Key on
}

/*
 * private 
 */

void Ym2612::write_data(uint8_t data) {
    digitalWriteFast(this->pin_cs, LOW);
    for (int i=0; i < 8; i++) {
        digitalWriteFast(this->pin_data[i], (data >> i) & 1);
    }
    delayMicroseconds(1);

    digitalWriteFast(this->pin_wr, LOW); // write data
    delayMicroseconds(5);
    digitalWriteFast(this->pin_wr, HIGH);
    delayMicroseconds(5);

    digitalWriteFast(this->pin_cs, HIGH);
}

void Ym2612::write_register(uint8_t reg, uint8_t data) {
    digitalWriteFast(this->pin_a0, LOW);
    write_data(reg);
    digitalWriteFast(this->pin_a0, HIGH);
    write_data(data);
}
