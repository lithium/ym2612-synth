#ifndef MIDI_H
#define MIDI_H

#include "config.h"

void setup_midi();


void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value);

// global
#define MIDI_CC_LFO_ENABLE 1
#define MIDI_CC_LFO_FREQUENCY 2


#define MIDI_CC_LFO_AM_DEPTH 38
#define MIDI_CC_LFO_FM_DEPTH 39

//settings
#define MIDI_CC_ALGORITHM 41
#define MIDI_CC_FEEDBACK 42

// tuning
#define MIDI_CC_DETUNE_OP1 45
#define MIDI_CC_DETUNE_OP2 46
#define MIDI_CC_DETUNE_OP3 47
#define MIDI_CC_DETUNE_OP4 48

#define MIDI_CC_MULTIPLY_OP1 49
#define MIDI_CC_MULTIPLY_OP2 50
#define MIDI_CC_MULTIPLY_OP3 51
#define MIDI_CC_MULTIPLY_OP4 52

// envelope cc's

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

#define MIDI_CC_DR_OP1 22
#define MIDI_CC_DR_OP2 23
#define MIDI_CC_DR_OP3 24
#define MIDI_CC_DR_OP4 25

#define MIDI_CC_SR_OP1 26
#define MIDI_CC_SR_OP2 27
#define MIDI_CC_SR_OP3 28
#define MIDI_CC_SR_OP4 29

#define MIDI_CC_SL_OP1 30
#define MIDI_CC_SL_OP2 31
#define MIDI_CC_SL_OP3 32
#define MIDI_CC_SL_OP4 33

#define MIDI_CC_RR_OP1 34
#define MIDI_CC_RR_OP2 35
#define MIDI_CC_RR_OP3 36
#define MIDI_CC_RR_OP4 37

#endif