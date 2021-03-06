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
    void initializeDefaultVoice();


    void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
    void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
    void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value);
    void handleMidiSysex(const uint8_t *data, uint16_t length, bool last);



    SynthVoice *getActiveVoice();


    void setListener(Ym2612::Listener *listener) {
        this->listener = listener;
        ym2612[0].setListener(listener);
        ym2612[1].setListener(listener);
    }

private:


    Ym2612::Listener *listener = nullptr;

    uint8_t active_voice_index;
    LinkedList<SynthVoice *> voices;
    Ym2612 ym2612[2];

};


extern Synth synth;

#endif