#include "midi.h"
#include "ym2612.h"
#include "patch.h"

void setup_midi()
{
    usbMIDI.setHandleNoteOn(handleMidiNoteOn);
    usbMIDI.setHandleNoteOff(handleMidiNoteOff);
    usbMIDI.setHandleControlChange(handleMidiCC);
    usbMIDI.setHandleSystemExclusive(handleMidiSysex);
}


uint8_t polyphonic_mode = POLY_MODE_POLY;
static uint8_t poly_notes[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};


//tuning scale from sega doc -- 1-1/2 steps flat
static uint16_t fnotes[12] = {617, 653, 692, 733, 777, 823, 872, 924, 979, 1037, 1099, 1164};


void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
    uint8_t ym_channel = 0xFF;
    if (polyphonic_mode == POLY_MODE_MONO) {
        ym_channel = channel-1;
    } else if (polyphonic_mode == POLY_MODE_POLY) {
        // find an available channel to play the note on
        for (int i=0; i < 6; i++) {
            if (poly_notes[i] == 0xFF) {
                poly_notes[i] = note;
                ym_channel = i;
                break;
            } 
        }
        if (ym_channel == 0xFF) {
            // no available channels
            return; 
        }
    }

    int midi_octave = (note/12)-1;
    int midi_scale_note = note % 12;
    uint16_t fn = fnotes[midi_scale_note];

    ym2612.setFrequency(ym_channel, midi_octave, fn);
    ym2612.keyOn(ym_channel);


    digitalWrite(PIN_LED, HIGH);
}

void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
    uint8_t ym_channel;
    if (polyphonic_mode == POLY_MODE_MONO) {
        ym_channel = channel-1;
    } else if (polyphonic_mode == POLY_MODE_POLY) {
        // find which channel the note is being played on
        for (int i=0; i < 6; i++) {
            if (poly_notes[i] == note) {
                poly_notes[i] = 0xFF;
                ym_channel = i;
                break;
            }
        }
    }

    ym2612.keyOff(ym_channel);

    digitalWrite(PIN_LED, LOW);
}

void handle_midi_for_channel(uint8_t ym_channel, uint8_t control, uint8_t value)
{
    switch (control) {
        case MIDI_CC_TL_OP1: ym2612.setTotalLevel(ym_channel, 0, value); break;
        case MIDI_CC_TL_OP2: ym2612.setTotalLevel(ym_channel, 1, value); break;
        case MIDI_CC_TL_OP3: ym2612.setTotalLevel(ym_channel, 2, value); break;
        case MIDI_CC_TL_OP4: ym2612.setTotalLevel(ym_channel, 3, value); break;

        case MIDI_CC_RS_OP1: ym2612.setRateScale(ym_channel, 0, value); break;
        case MIDI_CC_RS_OP2: ym2612.setRateScale(ym_channel, 1, value); break;
        case MIDI_CC_RS_OP3: ym2612.setRateScale(ym_channel, 2, value); break;
        case MIDI_CC_RS_OP4: ym2612.setRateScale(ym_channel, 3, value); break;

        case MIDI_CC_AR_OP1: ym2612.setAttackRate(ym_channel, 0, value); break;
        case MIDI_CC_AR_OP2: ym2612.setAttackRate(ym_channel, 1, value); break;
        case MIDI_CC_AR_OP3: ym2612.setAttackRate(ym_channel, 2, value); break;
        case MIDI_CC_AR_OP4: ym2612.setAttackRate(ym_channel, 3, value); break;

        case MIDI_CC_DR_OP1: ym2612.setDecayRate(ym_channel, 0, value); break;
        case MIDI_CC_DR_OP2: ym2612.setDecayRate(ym_channel, 1, value); break;
        case MIDI_CC_DR_OP3: ym2612.setDecayRate(ym_channel, 2, value); break;
        case MIDI_CC_DR_OP4: ym2612.setDecayRate(ym_channel, 3, value); break;

        case MIDI_CC_SR_OP1: ym2612.setSustainRate(ym_channel, 0, value); break;
        case MIDI_CC_SR_OP2: ym2612.setSustainRate(ym_channel, 1, value); break;
        case MIDI_CC_SR_OP3: ym2612.setSustainRate(ym_channel, 2, value); break;
        case MIDI_CC_SR_OP4: ym2612.setSustainRate(ym_channel, 3, value); break;

        case MIDI_CC_SL_OP1: ym2612.setSustainLevel(ym_channel, 0, value); break;
        case MIDI_CC_SL_OP2: ym2612.setSustainLevel(ym_channel, 1, value); break;
        case MIDI_CC_SL_OP3: ym2612.setSustainLevel(ym_channel, 2, value); break;
        case MIDI_CC_SL_OP4: ym2612.setSustainLevel(ym_channel, 3, value); break;

        case MIDI_CC_RR_OP1: ym2612.setReleaseRate(ym_channel, 0, value); break;
        case MIDI_CC_RR_OP2: ym2612.setReleaseRate(ym_channel, 1, value); break;
        case MIDI_CC_RR_OP3: ym2612.setReleaseRate(ym_channel, 2, value); break;
        case MIDI_CC_RR_OP4: ym2612.setReleaseRate(ym_channel, 3, value); break;

        case MIDI_CC_DETUNE_OP1: ym2612.setDetune(ym_channel, 0, value); break;
        case MIDI_CC_DETUNE_OP2: ym2612.setDetune(ym_channel, 1, value); break;
        case MIDI_CC_DETUNE_OP3: ym2612.setDetune(ym_channel, 2, value); break;
        case MIDI_CC_DETUNE_OP4: ym2612.setDetune(ym_channel, 3, value); break;

        case MIDI_CC_MULTIPLY_OP1: ym2612.setMultiple(ym_channel, 0, value); break;
        case MIDI_CC_MULTIPLY_OP2: ym2612.setMultiple(ym_channel, 1, value); break;
        case MIDI_CC_MULTIPLY_OP3: ym2612.setMultiple(ym_channel, 2, value); break;
        case MIDI_CC_MULTIPLY_OP4: ym2612.setMultiple(ym_channel, 3, value); break;

        case MIDI_CC_LFO_ENABLE_OP1: ym2612.enableLfoForOperator(ym_channel, 0, value); break;
        case MIDI_CC_LFO_ENABLE_OP2: ym2612.enableLfoForOperator(ym_channel, 1, value); break;
        case MIDI_CC_LFO_ENABLE_OP3: ym2612.enableLfoForOperator(ym_channel, 2, value); break;
        case MIDI_CC_LFO_ENABLE_OP4: ym2612.enableLfoForOperator(ym_channel, 3, value); break;

        case MIDI_CC_ALGORITHM: ym2612.setAlgorithm(ym_channel, value); break;
        case MIDI_CC_FEEDBACK: ym2612.setFeedback(ym_channel, value); break;

        case MIDI_CC_LFO_ENABLE: ym2612.enableLfo(value); break;
        case MIDI_CC_LFO_FREQUENCY: ym2612.setLfoFrequency(value); break;
        case MIDI_CC_LFO_AM_DEPTH: ym2612.setLfoAm(ym_channel, value); break;
        case MIDI_CC_LFO_FM_DEPTH: ym2612.setLfoFm(ym_channel, value); break;
    }

}


void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value)
{
    
    if (polyphonic_mode == POLY_MODE_POLY) {
        for (int i=0; i < 6; i++) {
            handle_midi_for_channel(i, control, value);
        }
    } else {
        handle_midi_for_channel(channel-1, control, value);
    }
}


void handleMidiSysex(const uint8_t *data, uint16_t length, bool last)
{
    Serial.print("sysex length: ");
    Serial.print(length);
    Serial.print(" last:");
    Serial.println(last);

    if (length < sysex_header_length) {
        // not a sysex message for us
        return;
    }

    struct sysex_header_t *header = (struct sysex_header_t *)data;

    if (memcmp(header->manufacturer_id, OUR_SYSEX_MANUFACTURER_CODE, 3) != 0)
    {
        Serial.println("manufacturer does NOT match!  ");
        return;
    }

    if (header->product_type != OUR_SYSEX_PRODUCT_TYPE || header->product_number != OUR_SYSEX_PRODUCT_NUMBER)
    {
        Serial.println("product type and number dont match");
        return;
    }

    Serial.print("sysex is good! command: ");
    Serial.println(header->command);

    if (header->command == SYSEX_COMMAND_REPLACE_PATCH) {
        sysex_replace_patch(header, data, length);
    }
    if (header->command == SYSEX_COMMAND_DUMP_PATCH) {
        sysex_dump_patch(header, data, length);
    }
}

void sysex_replace_patch(struct sysex_header_t *header, const uint8_t *data, uint16_t length)
{
    struct sysex_patch_header_t *patch_header = (struct sysex_patch_header_t *)(data + sysex_header_length);
    if (patch_header->patch_format == SYSEX_PATCH_FORMAT_TFI) {
        struct tfi_patch_t *tfi = (struct tfi_patch_t *)(patch_header + sysex_patch_header_length);
        ym2612.applyTfiPatch(patch_header->channel, tfi);
    }
}

void sysex_dump_patch(struct sysex_header_t *header, const uint8_t *data, uint16_t length)
{
    struct sysex_dump_patch_t *dump_msg = (struct sysex_dump_patch_t *)(data + sysex_header_length);

    auto patch_message_size = sysex_header_length + sysex_patch_header_length + sizeof(struct ym2612_patch_t) + 1;
    uint8_t message[patch_message_size];

    // midi sysex header
    struct sysex_header_t *response_header = (struct sysex_header_t *)message; 
    response_header->sysex_magic = 0xF0;
    memcpy(response_header->manufacturer_id, OUR_SYSEX_MANUFACTURER_CODE, 3);
    response_header->product_type = OUR_SYSEX_PRODUCT_TYPE;
    response_header->product_number = OUR_SYSEX_PRODUCT_NUMBER;
    response_header->command = SYSEX_COMMAND_REPLACE_PATCH;

    // replace current patch header
    struct sysex_patch_header_t *patch_header = (struct sysex_patch_header_t *)(message + sysex_header_length); 
    patch_header->channel = dump_msg->channel;
    patch_header->patch_format = SYSEX_PATCH_FORMAT_YM2612;

    // patch data
    struct ym2612_patch_t *cur_patch = (struct ym2612_patch_t *)(message + sysex_header_length + sysex_patch_header_length);
    ym2612.dumpPatch(dump_msg->channel, cur_patch); 

    // terminate sysex message
    message[patch_message_size-1] = 0xF7;  

    // send back
    usbMIDI.sendSysEx(patch_message_size, message, true);
}
