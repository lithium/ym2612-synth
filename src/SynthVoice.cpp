#include "SynthVoice.h"

SynthVoice::SynthVoice(Ym2612 *chips, int num_chips)
{
    this->chips = chips;
    this->num_chips = num_chips;
}

bool SynthVoice::midiMatch(uint8_t midi_channel, uint8_t midi_note)
{
    return 
        (this->midi_channel == midi_channel) &&
        (midi_note == -1 || (midi_note >= this->note_lo && midi_note <= this->note_hi))
        ;
}


void SynthVoice::keyOn()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].keyOn(channel);
        }
    }
}
void SynthVoice::keyOff()
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].keyOff(channel);
        }
    }
}


void SynthVoice::setDetune(uint8_t oper, uint8_t detune)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setDetune(channel, oper, detune);   
        }
    }
}
void SynthVoice::setMultiple(uint8_t oper, uint8_t multiple)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setMultiple(channel, oper, multiple);   
        }
    }
}
void SynthVoice::setTotalLevel(uint8_t oper, uint8_t level)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setTotalLevel(channel, oper, level);   
        }
    }
}
void SynthVoice::setRateScale(uint8_t oper, uint8_t rate_scale)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setRateScale(channel, oper, rate_scale);   
        }
    }
}
void SynthVoice::setAttackRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setAttackRate(channel, oper, rate);   
        }
    }
}
void SynthVoice::enableLfoForOperator(uint8_t oper, uint8_t enabled)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].enableLfoForOperator(channel, oper, enabled);   
        }
    }
}
void SynthVoice::setDecayRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setDecayRate(channel, oper, rate);   
        }
    }
}
void SynthVoice::setSustainRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setSustainRate(channel, oper, rate);   
        }
    }
}
void SynthVoice::setSustainLevel(uint8_t oper, uint8_t level)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setSustainLevel(channel, oper, level);   
        }
    }
}
void SynthVoice::setReleaseRate(uint8_t oper, uint8_t rate)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setReleaseRate(channel, oper, rate);   
        }
    }
}

void SynthVoice::setFrequency(uint8_t octave, uint16_t offset)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setFrequency(channel, octave, offset);   
        }
    }
}
void SynthVoice::setAlgorithm(uint8_t algorithm)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setAlgorithm(channel, algorithm);   
        }
    }
}
void SynthVoice::setFeedback(uint8_t feedback)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setFeedback(channel, feedback);   
        }
    }
}
void SynthVoice::setOutputs(uint8_t outputs)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setOutputs(channel, outputs);   
        }
    }
}
void SynthVoice::enableLfo(uint8_t enabled)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].enableLfo(enabled);   
        }
    }
}
void SynthVoice::setLfoFrequency(uint8_t frequency)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setLfoFrequency(frequency);   
        }
    }
}
void SynthVoice::setLfoAm(uint8_t depth)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setLfoAm(channel, depth);   
        }
    }
}
void SynthVoice::setLfoFm(uint8_t depth)
{
    for (auto i=0; i < (num_chips * CHANNELS_PER_CHIP); i++) {
        auto mask = 1<<i;
        if (this->ym2612_channels & mask) {
            auto chip = i % CHANNELS_PER_CHIP;
            auto channel = chip ? (mask >> CHANNELS_PER_CHIP) : mask;

            this->chips[chip].setLfoFm(channel, depth);   
        }
    }
}
