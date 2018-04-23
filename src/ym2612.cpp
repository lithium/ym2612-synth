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


    // chip enable
    digitalWriteFast(YM_IC, HIGH); 
    delay(1);
    digitalWriteFast(YM_IC, LOW); 
    delay(1);
    digitalWriteFast(YM_IC, HIGH); 

}



void Ym2612::writeRegister(uint8_t channel, uint8_t reg, uint8_t data)
{
    digitalWriteFast(this->pin_rd, HIGH);
    digitalWriteFast(this->pin_wr, LOW);

    digitalWriteFast(this->pin_cs, HIGH);

    // write address
    if (channel < 3) {
        digitalWriteFast(this->pin_a1, LOW);
        digitalWriteFast(this->pin_a0, LOW);
    } else {
        digitalWriteFast(this->pin_a1, HIGH);
        digitalWriteFast(this->pin_a0, LOW);
    }
    set_data(reg);
    digitalWriteFast(this->pin_cs, LOW);

    // delay after writing address
    delay_10ns();


    digitalWriteFast(this->pin_cs, HIGH);
    delay_10ns();


    // write data
    if (channel < 3) {
        digitalWriteFast(this->pin_a1, LOW);
        digitalWriteFast(this->pin_a0, HIGH);
    } else {
        digitalWriteFast(this->pin_a1, HIGH);
        digitalWriteFast(this->pin_a0, HIGH);
    }
    set_data(data);
    digitalWriteFast(this->pin_cs, LOW);

    // delay after writing data
    delay_10ns();
}


void Ym2612::keyOn(uint8_t channel)
{
    keyOnOperators(channel, 0xF); // turn all all 4 operators
}
void Ym2612::keyOff(uint8_t channel)
{
    keyOnOperators(channel, 0x0);
}
void Ym2612::keyOnOperators(uint8_t channel, uint8_t operators)
{
    writeRegister(channel, 0x28, (operators << 4) | (channel & 0x7));
}

void Ym2612::setOutputs(uint8_t left, uint8_t right)
{
    writeRegister(5, 0xb4, (left&1)<<7 | (right&1)<<6);
}

void Ym2612::setFrequency(uint8_t channel, uint8_t octave, uint16_t offset)
{
    uint8_t lsb_addr;
    uint8_t msb_addr;

    switch (channel) {
        case 0:
            lsb_addr = 0xA0;
            msb_addr = 0xA4;
            break;
        case 1:
            lsb_addr = 0xA1;
            msb_addr = 0xA5;
            break;
        case 2:
            lsb_addr = 0xA2;
            msb_addr = 0xA6;
            break;
    }
}

/*
 * private 
 */

void Ym2612::set_data(uint8_t b) 
{
    for (int i=0; i < 8; i++) {
        digitalWriteFast(this->pin_data[i], (b >> i) & 1);
    }
}

void Ym2612::delay_10ns()
{
    int i = DELAY_SCALE;
    while(i-- > 0) {
        __asm__ volatile ("nop");
    }
}
