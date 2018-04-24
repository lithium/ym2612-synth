#ifndef MIDI_H
#define MIDI_H

#include "config.h"

void setup_midi();


void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value);



#define MIDI_CC_TL_OP1 10
#define MIDI_CC_TL_OP2 11
#define MIDI_CC_TL_OP3 12
#define MIDI_CC_TL_OP4 13

#define MIDI_CC_RS_OP1 14
#define MIDI_CC_RS_OP2 15
#define MIDI_CC_RS_OP3 16
#define MIDI_CC_RS_OP4 17

#define MIDI_CC_AR_OP1 18
#define MIDI_CC_AR_OP2 19
#define MIDI_CC_AR_OP3 20
#define MIDI_CC_AR_OP4 21

#endif