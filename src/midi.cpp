#include "midi.h"
#include "ym2612.h"


void setup_midi()
{
    usbMIDI.setHandleNoteOn(handleMidiNoteOn);
    usbMIDI.setHandleNoteOff(handleMidiNoteOff);
    usbMIDI.setHandleControlChange(handleMidiCC);
}


//tuning scale from sega doc
static uint16_t fnotes[12] = {617, 653, 692, 733, 777, 823, 872, 924, 979, 1037, 1099, 1164};

void handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
    uint8_t ym_channel = channel-1;
    int midi_octave = (note/12)-1;
    int midi_scale_note = note % 12;
    uint16_t fn = fnotes[midi_scale_note];

    ym2612.setFrequency(ym_channel, midi_octave, fn);
    ym2612.keyOn(ym_channel);


    digitalWrite(PIN_LED, HIGH);
}

void handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
    ym2612.keyOff(channel - 1); 


    digitalWrite(PIN_LED, LOW);
}

void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value)
{

}
