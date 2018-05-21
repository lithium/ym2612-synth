#include "Synth.h"
#include "midi.h"

Synth synth;





Synth::Synth()
{

    active_voice_index = -1;
}     


void Synth::setup()
{
    this->ym2612[0].setup(YM_CS);
    this->ym2612[1].setup(YM2_CS);

    this->ym2612[0].reset();
    this->ym2612[1].reset();
}

void Synth::loadVoicesFromStorage()
{
    initializeDefaultVoice();
}

void Synth::initializeDefaultVoice()
{
    // initialize default voice, 12-note polyphony on midi ch1
    SynthVoice *voice = new SynthVoice(ym2612, 2);
    voice->ym2612_channels = 0xFC0; // all 12 channels
    voice->midi_channel = 1;
    voice->note_lo = 0;
    voice->note_hi = 127;
    voice->applyPatch((struct ym2612_patch_t *)&GrandPianoPatch);
    voice->setOutputs(3);

    voices.add(voice);
    active_voice_index = 0;

    Serial.println("default voice initialized");
}

SynthVoice *Synth::getActiveVoice() { 
    if (active_voice_index < 0 || active_voice_index >= this->voices.size()) {
        return nullptr;
    }
    return this->voices.get(active_voice_index); 
}


void Synth::handleMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
    auto l = voices.size();
    for (auto i=0; i < l; i++) {
        SynthVoice *v = voices.get(i);
        if (v->midiMatch(channel, note)) {

            v->noteOn(note, velocity);


        }
    }

}
void Synth::handleMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
    auto l = voices.size();
    for (auto i=0; i < l; i++) {
        SynthVoice *v = voices.get(i);
        if (v->midiMatch(channel, note)) {
            v->noteOff(note, velocity);
            // v->keyOff();
        }
    }

}
void Synth::handleMidiCC(uint8_t channel, uint8_t control, uint8_t value)
{
    auto l = voices.size();
    for (auto i=0; i < l; i++) {
        SynthVoice *v = voices.get(i);
        if (v->midiMatch(channel)) {

            switch (control) {
                case MIDI_CC_TL_OP1: v->setTotalLevel(0, value); break;
                case MIDI_CC_TL_OP2: v->setTotalLevel(1, value); break;
                case MIDI_CC_TL_OP3: v->setTotalLevel(2, value); break;
                case MIDI_CC_TL_OP4: v->setTotalLevel(3, value); break;

                case MIDI_CC_RS_OP1: v->setRateScale(0, value); break;
                case MIDI_CC_RS_OP2: v->setRateScale(1, value); break;
                case MIDI_CC_RS_OP3: v->setRateScale(2, value); break;
                case MIDI_CC_RS_OP4: v->setRateScale(3, value); break;

                case MIDI_CC_AR_OP1: v->setAttackRate(0, value); break;
                case MIDI_CC_AR_OP2: v->setAttackRate(1, value); break;
                case MIDI_CC_AR_OP3: v->setAttackRate(2, value); break;
                case MIDI_CC_AR_OP4: v->setAttackRate(3, value); break;

                case MIDI_CC_DR_OP1: v->setDecayRate(0, value); break;
                case MIDI_CC_DR_OP2: v->setDecayRate(1, value); break;
                case MIDI_CC_DR_OP3: v->setDecayRate(2, value); break;
                case MIDI_CC_DR_OP4: v->setDecayRate(3, value); break;

                case MIDI_CC_SR_OP1: v->setSustainRate(0, value); break;
                case MIDI_CC_SR_OP2: v->setSustainRate(1, value); break;
                case MIDI_CC_SR_OP3: v->setSustainRate(2, value); break;
                case MIDI_CC_SR_OP4: v->setSustainRate(3, value); break;

                case MIDI_CC_SL_OP1: v->setSustainLevel(0, value); break;
                case MIDI_CC_SL_OP2: v->setSustainLevel(1, value); break;
                case MIDI_CC_SL_OP3: v->setSustainLevel(2, value); break;
                case MIDI_CC_SL_OP4: v->setSustainLevel(3, value); break;

                case MIDI_CC_RR_OP1: v->setReleaseRate(0, value); break;
                case MIDI_CC_RR_OP2: v->setReleaseRate(1, value); break;
                case MIDI_CC_RR_OP3: v->setReleaseRate(2, value); break;
                case MIDI_CC_RR_OP4: v->setReleaseRate(3, value); break;

                case MIDI_CC_DETUNE_OP1: v->setDetune(0, value); break;
                case MIDI_CC_DETUNE_OP2: v->setDetune(1, value); break;
                case MIDI_CC_DETUNE_OP3: v->setDetune(2, value); break;
                case MIDI_CC_DETUNE_OP4: v->setDetune(3, value); break;

                case MIDI_CC_MULTIPLY_OP1: v->setMultiple(0, value); break;
                case MIDI_CC_MULTIPLY_OP2: v->setMultiple(1, value); break;
                case MIDI_CC_MULTIPLY_OP3: v->setMultiple(2, value); break;
                case MIDI_CC_MULTIPLY_OP4: v->setMultiple(3, value); break;

                case MIDI_CC_LFO_ENABLE_OP1: v->enableLfoForOperator(0, value); break;
                case MIDI_CC_LFO_ENABLE_OP2: v->enableLfoForOperator(1, value); break;
                case MIDI_CC_LFO_ENABLE_OP3: v->enableLfoForOperator(2, value); break;
                case MIDI_CC_LFO_ENABLE_OP4: v->enableLfoForOperator(3, value); break;

                case MIDI_CC_ALGORITHM: v->setAlgorithm(value); break;
                case MIDI_CC_FEEDBACK: v->setFeedback(value); break;

                case MIDI_CC_LFO_ENABLE: v->enableLfo(value); break;
                case MIDI_CC_LFO_FREQUENCY: v->setLfoFrequency(value); break;
                case MIDI_CC_LFO_AM_DEPTH: v->setLfoAm(value); break;
                case MIDI_CC_LFO_FM_DEPTH: v->setLfoFm(value); break;
            }


        }
    }
}




void Synth::handleMidiSysex(const uint8_t *data, uint16_t length, bool last)
{

}
