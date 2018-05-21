#include "SynthVoice.h"

static const uint16_t _scale_sega_doc[12] = {617, 653, 692, 733, 777, 823, 872, 924, 979, 1037, 1099, 1164};
static const uint16_t _scale_hand_tuned[12] = {686, 727, 770, 816, 865, 916, 970, 1028, 1089, 1154, 1223, 1295 };

SynthVoice::SynthVoice(Ym2612 *chips, int num_chips)
{
    this->chips = chips;
    this->num_chips = num_chips;
    this->used_channels = 0;
}

bool SynthVoice::midiMatch(uint8_t midi_channel, uint8_t midi_note)
{
    return 
        (this->midi_channel == midi_channel) &&
        (midi_note == -1 || (midi_note >= this->note_lo && midi_note <= this->note_hi))
        ;
}
uint8_t SynthVoice::poly_count() {
    uint8_t ret = 0;
    for (auto i=0; i < 12; i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            ret++;
        }
    }
    return ret;
}
void SynthVoice::noteOn(uint8_t midi_note, uint8_t velocity)
{
    int cur_key_count = note_assignments.size();
    if (cur_key_count >= poly_count()) {
        return;
    }
    for (auto i=0; i < 12; i++) {
        auto mask = 1<<i;
        if ((this->ym2612_channels & mask) && !(this->used_channels & mask)) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;
            struct note_assignment_t assign;


            assign.midi_note = midi_note;
            assign.chip = chip;
            assign.channel = channel;
            note_assignments.add(assign);
            used_channels |= mask;

            Serial.print("key on: ");
            Serial.print(" i="); Serial.print(i);
            Serial.print(" chip="); Serial.print(chip);
            Serial.print(" channel="); Serial.print(channel);
            Serial.print(" used="); Serial.println(used_channels, BIN);

            Serial.print("chips "); Serial.println((uint)this->chips, HEX);
            Serial.print("chip "); Serial.println((uint)&this->chips[chip], HEX);
            Serial.print("chip[0] "); Serial.println((uint)&this->chips[0], HEX);
            Serial.print("chip[1] "); Serial.println((uint)&this->chips[1], HEX);

            int midi_octave = (midi_note/12)-1;
            int midi_scale_note = midi_note % 12;
            uint16_t fn = _scale_hand_tuned[midi_scale_note];

            this->chips[chip].setFrequency(channel, midi_octave, fn);
            this->chips[chip].keyOn(channel);
            return;
        }
    }

}
void SynthVoice::noteOff(uint8_t midi_note, uint8_t velocity)
{
    auto l = note_assignments.size();
    for (auto i=0; i < l; i++) {
        struct note_assignment_t a = note_assignments.get(i);

        if (a.midi_note == midi_note) {
            this->chips[a.chip].keyOff(a.channel);
            note_assignments.remove(i);
            auto mask = (1<<a.channel) << (a.chip ? 6 : 0);
            used_channels &= ~mask;

            Serial.print("key off: ");
            Serial.print(" i="); Serial.print(i);
            Serial.print(" chip="); Serial.print(a.chip);
            Serial.print(" channel="); Serial.print(a.channel);
            Serial.print(" mask="); Serial.print(mask, BIN);
            Serial.print(" used="); Serial.println(used_channels, BIN);
            return;
        }
    }
}


void SynthVoice::keyOn()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].keyOn(channel);
        }
    }
}
void SynthVoice::keyOff()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].keyOff(channel);
        }
    }
}


void SynthVoice::setDetune(uint8_t oper, uint8_t detune)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setDetune(channel, oper, detune);   
        }
    }
}
void SynthVoice::setMultiple(uint8_t oper, uint8_t multiple)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setMultiple(channel, oper, multiple);   
        }
    }
}
void SynthVoice::setTotalLevel(uint8_t oper, uint8_t level)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setTotalLevel(channel, oper, level);   
        }
    }
}
void SynthVoice::setRateScale(uint8_t oper, uint8_t rate_scale)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setRateScale(channel, oper, rate_scale);   
        }
    }
}
void SynthVoice::setAttackRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setAttackRate(channel, oper, rate);   
        }
    }
}
void SynthVoice::enableLfoForOperator(uint8_t oper, uint8_t enabled)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].enableLfoForOperator(channel, oper, enabled);   
        }
    }
}
void SynthVoice::setDecayRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setDecayRate(channel, oper, rate);   
        }
    }
}
void SynthVoice::setSustainRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setSustainRate(channel, oper, rate);   
        }
    }
}
void SynthVoice::setSustainLevel(uint8_t oper, uint8_t level)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setSustainLevel(channel, oper, level);   
        }
    }
}
void SynthVoice::setReleaseRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setReleaseRate(channel, oper, rate);   
        }
    }
}

void SynthVoice::setFrequency(uint8_t octave, uint16_t offset)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            Serial.print("set frequency chip=");
            Serial.print(chip);
            Serial.print(" channel=");
            Serial.println(channel,BIN);

            this->chips[chip].setFrequency(channel, octave, offset);   
        }
    }
}
void SynthVoice::setAlgorithm(uint8_t algorithm)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setAlgorithm(channel, algorithm);   
        }
    }
}
void SynthVoice::setFeedback(uint8_t feedback)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setFeedback(channel, feedback);   
        }
    }
}
void SynthVoice::setOutputs(uint8_t outputs)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setOutputs(channel, outputs);   
        }
    }
}
void SynthVoice::enableLfo(uint8_t enabled)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            // auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].enableLfo(enabled);   
        }
    }
}
void SynthVoice::setLfoFrequency(uint8_t frequency)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            // auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setLfoFrequency(frequency);   
        }
    }
}
void SynthVoice::setLfoAm(uint8_t depth)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setLfoAm(channel, depth);   
        }
    }
}
void SynthVoice::setLfoFm(uint8_t depth)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].setLfoFm(channel, depth);   
        }
    }
}
void SynthVoice::applyPatch(struct ym2612_patch_t *patch)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;
            this->chips[chip].applyPatch(channel, patch);   
        }
    }
}

void SynthVoice::dumpPatch(struct ym2612_patch_t *patchDestination)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            this->chips[chip].dumpPatch(channel, patchDestination);   
            return; // abort after finding first
        }
    }
}


uint8_t SynthVoice::getDetune(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getDetune(channel, oper);
        }
    }
}

uint8_t SynthVoice::getMultiple(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getMultiple(channel, oper);
        }
    }
}
uint8_t SynthVoice::getTotalLevel(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getTotalLevel(channel, oper);
        }
    }
}
uint8_t SynthVoice::getRateScale(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getRateScale(channel, oper);
        }
    }
}
uint8_t SynthVoice::getAttackRate(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getAttackRate(channel, oper);
        }
    }
}
uint8_t SynthVoice::getLfoEnabledForOperator(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getLfoEnabledForOperator(channel, oper);
        }
    }
}
uint8_t SynthVoice::getDecayRate(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getDecayRate(channel, oper);
        }
    }
}
uint8_t SynthVoice::getSustainRate(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getSustainRate(channel, oper);
        }
    }
}
uint8_t SynthVoice::getSustainLevel(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getSustainLevel(channel, oper);
        }
    }
}
uint8_t SynthVoice::getReleaseRate(uint8_t oper)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getReleaseRate(channel, oper);
        }
    }
}

uint8_t SynthVoice::getFrequency()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getFrequency(channel);
        }
    }
}
uint8_t SynthVoice::getAlgorithm()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getAlgorithm(channel);
        }
    }
}
uint8_t SynthVoice::getFeedback()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getFeedback(channel);
        }
    }
}
uint8_t SynthVoice::getOutputs()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getOutputs(channel);
        }
    }
}
uint8_t SynthVoice::getLfoEnabled()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            // auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            return this->chips[chip].getLfoEnabled();
        }
    }
}
uint8_t SynthVoice::getLfoFrequency()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            // auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            return this->chips[chip].getLfoFrequency();
        }
    }
}
uint8_t SynthVoice::getLfoAm()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getLfoAm(channel);
        }
    }
}
uint8_t SynthVoice::getLfoFm()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i / CHANNELS_PER_CHIP;
            auto channel = chip ? (i - CHANNELS_PER_CHIP) : i;

            return this->chips[chip].getLfoFm(channel);
        }
    }
}
