#ifndef MIDI_H
#define MIDI_H

#include "config.h"



#define POLY_MODE_MONO 0
#define POLY_MODE_POLY 1
extern uint8_t polyphonic_mode;



const uint8_t OUR_SYSEX_MANUFACTURER_CODE[3] = {0x00, 0x7F, 0x38};
#define OUR_SYSEX_PRODUCT_TYPE 1
#define OUR_SYSEX_PRODUCT_NUMBER 1

#define SYSEX_COMMAND_REPLACE_PATCH 0
#define SYSEX_PATCH_FORMAT_TFI 0

struct sysex_header_t {
    uint8_t sysex_magic; // should be 0xF0
    uint8_t manufacturer_id[3];
    uint8_t product_type;
    uint8_t product_number;
    uint8_t command;
};
const uint sysex_header_length = sizeof(struct sysex_header_t);

struct sysex_patch_header_t {
    uint8_t channel;
    uint8_t patch_format;
};
const uint sysex_patch_header_length = sizeof(struct sysex_patch_header_t);




void setup_midi();


void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value);
void handleMidiSysex(const uint8_t *data, uint16_t length, bool last);

void sysex_replace_patch(struct sysex_header_t *header, const uint8_t *data, uint16_t length);




// http://little-scale.com/GENMDM/GENMDM_102/GENMDM_102.txt


// lfo
#define MIDI_CC_LFO_ENABLE 74
#define MIDI_CC_LFO_FREQUENCY 1
#define MIDI_CC_LFO_AM_DEPTH 76
#define MIDI_CC_LFO_FM_DEPTH 75

//settings
#define MIDI_CC_ALGORITHM 14
#define MIDI_CC_FEEDBACK 15

// tuning
#define MIDI_CC_DETUNE_OP1 24
#define MIDI_CC_DETUNE_OP2 25
#define MIDI_CC_DETUNE_OP3 26
#define MIDI_CC_DETUNE_OP4 27

#define MIDI_CC_MULTIPLY_OP1 20
#define MIDI_CC_MULTIPLY_OP2 21
#define MIDI_CC_MULTIPLY_OP3 22
#define MIDI_CC_MULTIPLY_OP4 23

// envelope cc's

#define MIDI_CC_TL_OP1 16
#define MIDI_CC_TL_OP2 17
#define MIDI_CC_TL_OP3 18
#define MIDI_CC_TL_OP4 19

#define MIDI_CC_RS_OP1 39
#define MIDI_CC_RS_OP2 40
#define MIDI_CC_RS_OP3 41
#define MIDI_CC_RS_OP4 42

#define MIDI_CC_AR_OP1 43
#define MIDI_CC_AR_OP2 44
#define MIDI_CC_AR_OP3 45
#define MIDI_CC_AR_OP4 46

#define MIDI_CC_DR_OP1 47
#define MIDI_CC_DR_OP2 48
#define MIDI_CC_DR_OP3 49
#define MIDI_CC_DR_OP4 50

#define MIDI_CC_SR_OP1 51
#define MIDI_CC_SR_OP2 52
#define MIDI_CC_SR_OP3 53
#define MIDI_CC_SR_OP4 54

#define MIDI_CC_SL_OP1 55
#define MIDI_CC_SL_OP2 56
#define MIDI_CC_SL_OP3 57
#define MIDI_CC_SL_OP4 58

#define MIDI_CC_RR_OP1 59
#define MIDI_CC_RR_OP2 60
#define MIDI_CC_RR_OP3 61
#define MIDI_CC_RR_OP4 62

#define MIDI_CC_LFO_ENABLE_OP1 70
#define MIDI_CC_LFO_ENABLE_OP2 71
#define MIDI_CC_LFO_ENABLE_OP3 72
#define MIDI_CC_LFO_ENABLE_OP4 73

#endif