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
    void write_register(uint8_t part, uint8_t reg, uint8_t data);


    // global registers  0x22 - 0x2B
    void enableLfo(bool enabled);
    void setLfoFrequency(uint8_t frequency);

    void setCh3Mode(uint8_t mode);

    void setKeyOnOff(uint8_t channel, uint8_t operators);
    void keyOn(uint8_t channel);
    void keyOff(uint8_t channel);

    void enableDac(bool enabled);
    void setDac(uint16_t dac_value);

    // channel+slot  0x30 - 0x90
    void setDetune(uint8_t channel, uint8_t oper, uint8_t detune);
    void setMultiple(uint8_t channel, uint8_t oper, uint8_t multiple);
    void setTotalLevel(uint8_t channel, uint8_t oper, uint8_t level);
    void setRateScale(uint8_t channel, uint8_t oper, uint8_t rate_scale);
    void setAttack(uint8_t channel, uint8_t oper, uint8_t rate);
    void enableLfoAm(uint8_t channel, uint8_t oper, bool enabled);
    void setFirstDecay(uint8_t channel, uint8_t oper, uint8_t rate);
    void setSecondDecay(uint8_t channel, uint8_t oper, uint8_t rate);
    void setSecondLevel(uint8_t channel, uint8_t oper, uint8_t level);
    void setRelease(uint8_t channel, uint8_t oper, uint8_t rate);

    // channel  0xA0 - 0xB4
    void setFrequency(uint8_t channel, uint8_t octave, uint16_t offset);
    void setAlgorithm(uint8_t channel, uint8_t algorithm, uint8_t feedback);
    void setOutputs(uint8_t channel, bool left, bool right);
    void setLfoAm(uint8_t channel, uint8_t depth);
    void setLfoFm(uint8_t channel, uint8_t depth);


    static uint16_t hz_to_fword(uint8_t octave, uint16_t hz);


private:
    uint8_t pin_data[8];
    uint8_t pin_ic;
    uint8_t pin_cs;
    uint8_t pin_rd;
    uint8_t pin_wr;
    uint8_t pin_a0;
    uint8_t pin_a1;


    void update_ch_register(uint8_t base_addr, uint8_t channel, uint8_t bit_offset, uint8_t value);
    void update_chop_register(uint8_t base_addr, uint8_t channel, uint8_t oper, uint8_t bit_offset, uint8_t value);
    void update_register(uint8_t ym_addr, uint8_t channel, uint8_t bit_offset, uint8_t value);

    void set_register(uint8_t part, uint8_t ym_addr, uint8_t value);
    uint8_t get_register(uint8_t part, uint8_t ym_addr);

    // internal register cache, copy on write
#define YM_REG_LAST_ADDR 0xB4
#define YM_REG_FIRST_ADDR 0x22
#define YM_REG_PART_SIZE (YM_REG_LAST_ADDR - YM_REG_FIRST_ADDR) 
#define YM_REG_NUM_PARTS 2
    uint8_t registers[YM_REG_NUM_PARTS][YM_REG_PART_SIZE];

};


extern Ym2612 ym2612;


#endif