#ifndef SYNTH_H
#define SYNTH_H

#include "config.h"
#include "ym2612.h"
#include "internal_storage.h"

#include "SynthVoice.h"

class Synth 
{
public:
    Synth();

    void setup();

    void loadVoicesFromStorage();


    void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
    void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
    void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value);
    void handleMidiSysex(const uint8_t *data, uint16_t length, bool last);


    const uint16_t *getScale() { return this->scale; }


private:

    const uint16_t *scale; 


    LinkedList<SynthVoice *> voices;
    Ym2612 ym2612[2];
};


extern Synth synth;

#endif