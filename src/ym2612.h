#ifndef YM2612_H
#define YM2612_h

#include "config.h"


#define DELAY_SCALE 11


class Ym2612 {
public:
    Ym2612(
        uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
        uint8_t ic, uint8_t cs, uint8_t rd, uint8_t wr, uint8_t a0, uint8_t a1
    );
    void setup();


    void writeRegister(uint8_t channel, uint8_t reg, uint8_t data);

    void keyOn(uint8_t channel);
    void keyOff(uint8_t channel);
    void keyOnOperators(uint8_t channel, uint8_t operators);

    void setOutputs(uint8_t left, uint8_t right);

    void setFrequency(uint8_t channel, uint8_t octave, uint16_t offset);


private:
    uint8_t pin_data[8];
    uint8_t pin_ic;
    uint8_t pin_cs;
    uint8_t pin_rd;
    uint8_t pin_wr;
    uint8_t pin_a0;
    uint8_t pin_a1;

    void set_data(uint8_t b);
    void delay_10ns();
};


extern Ym2612 ym2612;


#endif