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
    void reset();
    void segaDocTestProgram();

    // utility functions
    void write_data(uint8_t data);
    void write_register(uint8_t reg, uint8_t data);


/*
    // global registers
    void enableLfo(bool enabled);
    void setLfoFrequency(uint8_t frequency); //freq=0..7
    void enableDac(bool enabled);
    void setDac(uint16_t dac_value);
    void setCh3Mode(uint8_t mode); // 0=normal, 1=channel3 4 separate frequencies


    // channel
    void keyOnOperators(uint8_t channel, uint8_t operators);
    void keyOn(uint8_t channel);
    void keyOff(uint8_t channel);
    void setFrequency(uint8_t channel, uint8_t octave, uint16_t offset);
    void setAlgorithm(uint8_t channel, uint8_t algorithm, uint8_t feedback);
    void setOutputs(uint8_t channel, bool left, bool right);
    void setLfoFm(uint8_t channel, uint8_t depth);
    void setLfoFm(uint8_t channel, uint8_t depth);


    // channel+operator
    void setDetune(uint8_t channel, uint8_t operator, uint8_t detune);
    void setMultiple(uint8_t channel, uint8_t operator, uint8_t multiple);
    void setTotalLevel(uint8_t channel, uint8_t operator, uint8_t level);
    void setRateScale(uint8_t channel, uint8_t operator, uint8_t rate_scale);
    void enableLfoAm(uint8_t channel, uint8_t operator, bool enabled);
    void setAttack(uint8_t channel, uint8_t operator, uint8_t rate);
    void setFirstDecay(uint8_t channel, uint8_t operator, uint8_t rate);
    void setSecondDecay(uint8_t channel, uint8_t operator, uint8_t rate);
    void setSecondLevel(uint8_t channel, uint8_t operator, uint8_t level);
    void setRelease(uint8_t channel, uint8_t operator, uint8_t rate);
*/


private:
    uint8_t pin_data[8];
    uint8_t pin_ic;
    uint8_t pin_cs;
    uint8_t pin_rd;
    uint8_t pin_wr;
    uint8_t pin_a0;
    uint8_t pin_a1;

};


extern Ym2612 ym2612;


#endif