#ifndef MIDI_H
#define MIDI_H

#include "config.h"

void setup_midi();


void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value);


#endif