#ifndef YM2612_H
#define YM2612_H

#include "config.h"
#include "patch.h"
#include <LinkedList.h>



class Ym2612 {
public:
    Ym2612(
        uint8_t cs=-1,
        uint8_t d0=YM_D0, uint8_t d1=YM_D1, uint8_t d2=YM_D2, uint8_t d3=YM_D3, uint8_t d4=YM_D4, uint8_t d5=YM_D5, uint8_t d6=YM_D6, uint8_t d7=YM_D7,
        uint8_t ic=YM_IC, uint8_t rd=-1, uint8_t wr=YM_WR, uint8_t a0=YM_A0, uint8_t a1=YM_A1
    );

    void setup(
        uint8_t cs, 
        uint8_t d0=YM_D0, uint8_t d1=YM_D1, uint8_t d2=YM_D2, uint8_t d3=YM_D3, uint8_t d4=YM_D4, uint8_t d5=YM_D5, uint8_t d6=YM_D6, uint8_t d7=YM_D7,
        uint8_t ic=YM_IC, uint8_t rd=-1, uint8_t wr=YM_WR, uint8_t a0=YM_A0, uint8_t a1=YM_A1
    );

    void reset();

    void applyTfiPatch(uint8_t channel, struct tfi_patch_t *patch);
    void applyPatch(uint8_t channel, struct ym2612_patch_t *patch);
    void dumpPatch(uint8_t channel, struct ym2612_patch_t *patchDestination);

    void grandPianoVoice(uint8_t channel);
    void segaDocTestProgram(bool play_test_note);
    void segaDocTestProgramCh4(bool play_test_note);

    void setPatchName(char *name);
    char *getPatchName();


    // utility functions
    void write_data(uint8_t data);
    void write_register(uint8_t part, uint8_t reg, uint8_t data);


    // global registers  0x22 - 0x2B
    void enableLfo(uint8_t enabled);
    uint8_t getLfoEnabled();

    void setLfoFrequency(uint8_t frequency);
    uint8_t getLfoFrequency();

    void setCh3Mode(uint8_t mode);
    uint8_t getCh3Mode();

    void setKeyOnOff(uint8_t channel, uint8_t operators);
    void keyOn(uint8_t channel);
    void keyOff(uint8_t channel);

    void enableDac(uint8_t enabled);
    uint8_t getDacEnabled();
    void setDac(uint16_t dac_value);


    // channel+slot  0x30 - 0x90
    void setDetune(uint8_t channel, uint8_t oper, uint8_t detune);
    void setMultiple(uint8_t channel, uint8_t oper, uint8_t multiple);
    void setTotalLevel(uint8_t channel, uint8_t oper, uint8_t level);
    void setRateScale(uint8_t channel, uint8_t oper, uint8_t rate_scale);
    void setAttackRate(uint8_t channel, uint8_t oper, uint8_t rate);
    void enableLfoForOperator(uint8_t channel, uint8_t oper, uint8_t enabled);
    void setDecayRate(uint8_t channel, uint8_t oper, uint8_t rate);
    void setSustainRate(uint8_t channel, uint8_t oper, uint8_t rate);
    void setSustainLevel(uint8_t channel, uint8_t oper, uint8_t level);
    void setReleaseRate(uint8_t channel, uint8_t oper, uint8_t rate);

    uint8_t getDetune(uint8_t channel, uint8_t oper);
    uint8_t getMultiple(uint8_t channel, uint8_t oper);
    uint8_t getTotalLevel(uint8_t channel, uint8_t oper);
    uint8_t getRateScale(uint8_t channel, uint8_t oper);
    uint8_t getAttackRate(uint8_t channel, uint8_t oper);
    uint8_t getLfoEnabledForOperator(uint8_t channel, uint8_t oper);
    uint8_t getDecayRate(uint8_t channel, uint8_t oper);
    uint8_t getSustainRate(uint8_t channel, uint8_t oper);
    uint8_t getSustainLevel(uint8_t channel, uint8_t oper);
    uint8_t getReleaseRate(uint8_t channel, uint8_t oper);

    // channel  0xA0 - 0xB4
    void setFrequency(uint8_t channel, uint8_t octave, uint16_t offset);
    void setAlgorithm(uint8_t channel, uint8_t algorithm);
    void setFeedback(uint8_t channel, uint8_t feedback);
    void setOutputs(uint8_t channel, uint8_t outputs);
    void setLfoAm(uint8_t channel, uint8_t depth);
    void setLfoFm(uint8_t channel, uint8_t depth);

    uint8_t getFrequency(uint8_t channel);
    uint8_t getAlgorithm(uint8_t channel);
    uint8_t getFeedback(uint8_t channel);
    uint8_t getOutputs(uint8_t channel);
    uint8_t getLfoAm(uint8_t channel);
    uint8_t getLfoFm(uint8_t channel);


    class Listener {
    public:
        virtual void settingsChanged(uint8_t channel, uint8_t oper) = 0; // -1 means change applies to all channels/operators
    };
    void addListener(Listener *listener);
    void removeListener(Listener *listener);
    void notifyListenersOfChange(uint8_t channel, uint8_t oper);


    static uint16_t hz_to_fword(uint8_t octave, uint16_t hz);




private:
    uint8_t pin_data[8];
    uint8_t pin_ic;
    uint8_t pin_cs;
    uint8_t pin_rd;
    uint8_t pin_wr;
    uint8_t pin_a0;
    uint8_t pin_a1;

    char patch_name[PATCH_NAME_LENGTH + 1];


    void update_ch_register(uint8_t base_addr, uint8_t channel, uint8_t mask, uint8_t value);
    void update_chop_register(uint8_t base_addr, uint8_t channel, uint8_t oper, uint8_t mask, uint8_t value);
    void update_register(uint8_t ym_addr, uint8_t channel, uint8_t mask, uint8_t value);

    uint8_t get_ch_register(uint8_t base_addr, uint8_t channel, uint8_t mask);
    uint8_t get_chop_register(uint8_t base_addr, uint8_t channel, uint8_t oper, uint8_t mask);

    void set_register(uint8_t part, uint8_t ym_addr, uint8_t value);
    uint8_t get_register(uint8_t part, uint8_t ym_addr);

    // internal register cache, copy on write
#define YM_REG_LAST_ADDR 0xB9
#define YM_REG_FIRST_ADDR 0x22
#define YM_REG_PART_SIZE (YM_REG_LAST_ADDR - YM_REG_FIRST_ADDR)  
#define YM_REG_NUM_PARTS 2
    uint8_t registers[YM_REG_NUM_PARTS][YM_REG_PART_SIZE];

    LinkedList<Listener*> listeners;

};


extern Ym2612 ym2612;


#endif