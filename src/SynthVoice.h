#ifndef SYNTH_VOICE_H
#define SYNTH_VOICE_H

#include "ym2612.h"

// channel selection
// bit: 7 6 5 4 3 2 1 0
//           

#define NUM_CHIPS 2
#define CHANNELS_PER_CHIP 6


class SynthVoice
{
public:
    SynthVoice(Ym2612 *chips, int num_chips=2);

    Ym2612 *chips;
    int num_chips;

    char name[17];
    char patch_name[17];

    uint16_t ym2612_channels;   // 12 bit mask

    uint8_t midi_channel=1;
    uint8_t note_lo=0;
    uint8_t note_hi=127;
    uint8_t midi_transpose=0;

    bool midiMatch(uint8_t midi_channel, uint8_t midi_note=-1);

    void dumpPatch(struct ym2612_patch_t *patchDestination);

    void keyOn();
    void keyOff();

    void setDetune(uint8_t oper, uint8_t detune);
    void setMultiple(uint8_t oper, uint8_t multiple);
    void setTotalLevel(uint8_t oper, uint8_t level);
    void setRateScale(uint8_t oper, uint8_t rate_scale);
    void setAttackRate(uint8_t oper, uint8_t rate);
    void enableLfoForOperator(uint8_t oper, uint8_t enabled);
    void setDecayRate(uint8_t oper, uint8_t rate);
    void setSustainRate(uint8_t oper, uint8_t rate);
    void setSustainLevel(uint8_t oper, uint8_t level);
    void setReleaseRate(uint8_t oper, uint8_t rate);
    
    void setFrequency(uint8_t octave, uint16_t offset);
    void setAlgorithm(uint8_t algorithm);
    void setFeedback(uint8_t feedback);
    void setOutputs(uint8_t outputs);
    void enableLfo(uint8_t enabled);
    void setLfoFrequency(uint8_t frequency);
    void setLfoAm(uint8_t depth);
    void setLfoFm(uint8_t depth);


    uint8_t getDetune(uint8_t oper);
    uint8_t getMultiple(uint8_t oper);
    uint8_t getTotalLevel(uint8_t oper);
    uint8_t getRateScale(uint8_t oper);
    uint8_t getAttackRate(uint8_t oper);
    uint8_t getLfoEnabledForOperator(uint8_t oper);
    uint8_t getDecayRate(uint8_t oper);
    uint8_t getSustainRate(uint8_t oper);
    uint8_t getSustainLevel(uint8_t oper);
    uint8_t getReleaseRate(uint8_t oper);

    uint8_t getFrequency();
    uint8_t getAlgorithm();
    uint8_t getFeedback();
    uint8_t getOutputs();
    uint8_t getLfoEnabled();
    uint8_t getLfoFrequency();
    uint8_t getLfoAm();
    uint8_t getLfoFm();

};

#endif
