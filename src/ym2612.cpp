#include "ym2612.h"
#include "config.h"
#include "clock.h"


Ym2612 ym2612(
    YM_D0, YM_D1, YM_D2, YM_D3, YM_D4, YM_D5, YM_D6, YM_D7,
    YM_IC, YM_CS, YM_RD, YM_WR, YM_A0, YM_A1
);

Ym2612::Ym2612(
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t ic, uint8_t cs, uint8_t rd, uint8_t wr, uint8_t a0, uint8_t a1
)
{
    this->pin_data[0] = d0;
    this->pin_data[1] = d1;
    this->pin_data[2] = d2;
    this->pin_data[3] = d3;
    this->pin_data[4] = d4;
    this->pin_data[5] = d5;
    this->pin_data[6] = d6;
    this->pin_data[7] = d7;
    this->pin_ic = ic;
    this->pin_cs = cs;
    this->pin_rd = rd;
    this->pin_wr = wr;
    this->pin_a0 = a0;
    this->pin_a1 = a1;

}

void Ym2612::setup()
{
    // setup pins as outputs
    for (int i=0; i < 8; i++) {
        pinMode(this->pin_data[i], OUTPUT);
    }
    pinMode(this->pin_ic, OUTPUT);
    pinMode(this->pin_cs, OUTPUT);
    pinMode(this->pin_rd, OUTPUT);
    pinMode(this->pin_wr, OUTPUT);
    pinMode(this->pin_a0, OUTPUT);
    pinMode(this->pin_a1, OUTPUT);

    // default pin states
    digitalWriteFast(this->pin_ic, HIGH);
    digitalWriteFast(this->pin_cs, HIGH);
    digitalWriteFast(this->pin_wr, HIGH);
    digitalWriteFast(this->pin_rd, HIGH);
    digitalWriteFast(this->pin_a0, LOW);
    digitalWriteFast(this->pin_a1, LOW);

    // clear internal registers
    memset(this->registers, 0, sizeof(this->registers));
}

uint16_t Ym2612::hz_to_fword(uint8_t octave, uint16_t hz)
{
    // (144 * fnote * 2^20 / CLK) / 2^(B-1)
    uint16_t fnum = ((144 * hz * 1048576) / MASTER_CLOCK_SPEED) / pow(2, octave - 1);
    return fnum;
}

void Ym2612::applyTfiPatch(uint8_t channel, struct tfi_patch_t *patch)
{
    setAlgorithm(channel, patch->algorithm);
    setFeedback(channel, patch->feedback);
    for (int i=0; i < 4; i++) {
        setMultiple(channel, i, patch->op[i].multiplier);
        setDetune(channel, i, patch->op[i].detune);
        setTotalLevel(channel, i, patch->op[i].total_level);
        setRateScale(channel, i, patch->op[i].rate_scale);
        setAttackRate(channel, i, patch->op[i].attack_rate);
        setDecayRate(channel, i, patch->op[i].decay_rate);
        setSustainRate(channel, i, patch->op[i].sustain_rate);
        setReleaseRate(channel, i, patch->op[i].release_rate);
        setSustainLevel(channel, i, patch->op[i].sustain_level);
    }
}

void Ym2612::dumpPatch(uint8_t channel, struct ym2612_patch_t *patch)
{
    memset(patch, 0, sizeof(struct ym2612_patch_t));

    // channel-global parameters
    patch->lfo_enabled = getLfoEnabled();
    patch->lfo_frequency = getLfoFrequency();
    patch->lfo_am_depth = getLfoAm(channel);
    patch->lfo_fm_depth = getLfoFm(channel);

    patch->algorithm = getAlgorithm(channel);
    patch->feedback = getFeedback(channel);

    // channel+op parameters
    for (int i=0; i < 4; i++) {
        patch->op[i].detune = getDetune(channel, i);
        patch->op[i].multiplier = getMultiple(channel, i);
        patch->op[i].total_level = getTotalLevel(channel, i);
        patch->op[i].sustain_level = getSustainLevel(channel, i);
        patch->op[i].rate_scale = getRateScale(channel, i);
        patch->op[i].attack_rate = getAttackRate(channel, i);
        patch->op[i].decay_rate = getDecayRate(channel, i);
        patch->op[i].sustain_rate = getSustainRate(channel, i);
        patch->op[i].release_rate = getReleaseRate(channel, i);
        patch->op[i].lfo_enabled = getLfoEnabledForOperator(channel, i);
        // patch->op[i].frequency = getFrequency(channel, i);
    }
}

/*
 * global registers
 */

void Ym2612::enableLfo(uint8_t enabled)
{
    update_register(0x22,0, 0b00001000, enabled);
}
uint8_t Ym2612::getLfoEnabled()
{
    return get_ch_register(0x22,0, 0b00001000);
}

void Ym2612::setLfoFrequency(uint8_t frequency)
{
    update_register(0x22,0, 0b00000111, frequency);
}
uint8_t Ym2612::getLfoFrequency()
{
    return get_ch_register(0x22,0, 0b00000111);
}

void Ym2612::setCh3Mode(uint8_t mode)
{
    update_register(0x27,0, 0b11000000, mode);
}
uint8_t Ym2612::getCh3Mode()
{
    return get_ch_register(0x27,0, 0b11000000);
}

void Ym2612::setKeyOnOff(uint8_t channel, uint8_t operators)
{
    if (channel >= 3) {
        channel += 1;
    }
    write_register(0, 0x28, ((operators & 0xF) <<4) | (channel & 0x7));
}
void Ym2612::keyOn(uint8_t channel)
{
    setKeyOnOff(channel, 0xF);
}
void Ym2612::keyOff(uint8_t channel)
{
    setKeyOnOff(channel, 0x0);
}

void Ym2612::enableDac(uint8_t enabled)
{
    update_register(0x2B,0, 0b10000000, enabled);
}
uint8_t Ym2612::getDacEnabled()
{
    return get_ch_register(0x2B,0, 0b10000000);
}

void Ym2612::setDac(uint16_t dac_value)
{
    update_register(0x2A,0, 0b11111111, dac_value);
}


/*
 * channel+operator registers
 */

void Ym2612::setDetune(uint8_t channel, uint8_t oper, uint8_t detune)
{
    update_chop_register(0x30,channel,oper, 0b01110000, detune);

}
uint8_t Ym2612::getDetune(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x30,channel,oper, 0b01110000);
}

void Ym2612::setMultiple(uint8_t channel, uint8_t oper, uint8_t multiple)
{
    update_chop_register(0x30,channel,oper, 0b00001111, multiple);
}
uint8_t Ym2612::getMultiple(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x30,channel,oper, 0b00001111);
}

void Ym2612::setTotalLevel(uint8_t channel, uint8_t oper, uint8_t level)
{
    update_chop_register(0x40,channel,oper, 0b01111111, level);
}
uint8_t Ym2612::getTotalLevel(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x40,channel,oper, 0b01111111);
}

void Ym2612::setRateScale(uint8_t channel, uint8_t oper, uint8_t rate_scale)
{
    update_chop_register(0x50,channel,oper, 0b11000000, rate_scale); 
}
uint8_t Ym2612::getRateScale(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x50,channel,oper, 0b11000000);
}

void Ym2612::setAttackRate(uint8_t channel, uint8_t oper, uint8_t rate)
{
    update_chop_register(0x50,channel,oper, 0b00011111, rate);
}
uint8_t Ym2612::getAttackRate(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x50,channel,oper, 0b00011111);
}

void Ym2612::enableLfoForOperator(uint8_t channel, uint8_t oper, uint8_t enabled)
{
    update_chop_register(0x60,channel,oper, 0b10000000, enabled);
}
uint8_t Ym2612::getLfoEnabledForOperator(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x60,channel,oper, 0b10000000);
}

void Ym2612::setDecayRate(uint8_t channel, uint8_t oper, uint8_t rate)
{
    update_chop_register(0x60,channel,oper, 0b00011111, rate);
}
uint8_t Ym2612::getDecayRate(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x60,channel,oper, 0b00011111);
}

void Ym2612::setSustainRate(uint8_t channel, uint8_t oper, uint8_t rate)
{
    update_chop_register(0x70,channel,oper, 0b00011111, rate);
}
uint8_t Ym2612::getSustainRate(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x70,channel,oper, 0b00011111);
}

void Ym2612::setSustainLevel(uint8_t channel, uint8_t oper, uint8_t level)
{
    update_chop_register(0x80,channel,oper, 0b11110000, level);
}
uint8_t Ym2612::getSustainLevel(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x80,channel,oper, 0b11110000);
}

void Ym2612::setReleaseRate(uint8_t channel, uint8_t oper, uint8_t rate)
{
    update_chop_register(0x80,channel,oper, 0b00001111, rate);
}
uint8_t Ym2612::getReleaseRate(uint8_t channel, uint8_t oper)
{
    return get_chop_register(0x80,channel,oper, 0b00001111);
}


/* 
 * channel registers
 */
void Ym2612::setFrequency(uint8_t channel, uint8_t octave, uint16_t freq)
{   
    uint8_t lsb = freq & 0xFF;
    uint8_t msb = (freq & 0x700)>>8;

    // TODO: handle Ch3 mode with diff frequencies
    uint8_t ym_addr = 0xA0 + (channel % 3);

    // set high order byte first
    set_register(channel >= 3, ym_addr+4, ((octave & 0x7)<<3) | msb);
    set_register(channel >= 3, ym_addr, lsb);
}


void Ym2612::setAlgorithm(uint8_t channel, uint8_t algorithm)
{
    update_ch_register(0xB0, channel, 0b00000111, algorithm);
}
uint8_t Ym2612::getAlgorithm(uint8_t channel)
{
    return get_ch_register(0xB0, channel, 0b00000111);
}

void Ym2612::setFeedback(uint8_t channel, uint8_t feedback) 
{
    update_ch_register(0xB0, channel, 0b00111000, feedback);
}
uint8_t Ym2612::getFeedback(uint8_t channel)
{
    return get_ch_register(0xB0, channel, 0b00111000);
}

void Ym2612::setOutputs(uint8_t channel, uint8_t outputs)
{
    update_ch_register(0xB4, channel, 0b11000000, outputs);
}
uint8_t Ym2612::getOutputs(uint8_t channel)
{
    return get_ch_register(0xB4, channel, 0b11000000);
}

void Ym2612::setLfoAm(uint8_t channel, uint8_t depth)
{
    update_ch_register(0xB4, channel, 0b00011000, depth);
}
uint8_t Ym2612::getLfoAm(uint8_t channel)
{
    return get_ch_register(0xB4, channel, 0b00011000);
}

void Ym2612::setLfoFm(uint8_t channel, uint8_t depth)
{
    update_ch_register(0xB4, channel, 0b00000111, depth);
}
uint8_t Ym2612::getLfoFm(uint8_t channel)
{
    return get_ch_register(0xB4, channel, 0b00000111);
}


/*
 * internal register cache
 */
uint8_t Ym2612::get_ch_register(uint8_t base_addr, uint8_t channel, uint8_t mask)
{
    uint8_t ym_addr = base_addr + (channel%3);
    uint8_t value = get_register(channel >= 3, ym_addr) & mask;
    while (!(mask & 1)) {
        value >>= 1;
        mask >>= 1;
    }
    return value;
}

uint8_t Ym2612::get_chop_register(uint8_t base_addr,uint8_t channel,uint8_t oper, uint8_t mask)
{
    uint8_t ym_addr = base_addr + (oper*4) + (channel%3);
    uint8_t value = get_register(channel >= 3, ym_addr) & mask;
    while (!(mask & 1)) {
        value >>= 1;
        mask >>= 1;
    }
    return value;
}

void Ym2612::update_ch_register(uint8_t base_addr, uint8_t channel, uint8_t mask, uint8_t value)
{
    uint8_t ym_addr = base_addr + (channel%3);
    return update_register(ym_addr, channel, mask, value);
}

void Ym2612::update_chop_register(uint8_t base_addr,uint8_t channel,uint8_t oper, uint8_t mask, uint8_t value)
{
    uint8_t ym_addr = base_addr + oper*4 + (channel%3);
    return update_register(ym_addr, channel, mask, value);
}

void Ym2612::update_register(uint8_t ym_addr, uint8_t channel, uint8_t mask, uint8_t value)
{
    uint8_t existing_value = get_register(channel >= 3 ? 1 : 0, ym_addr);

    uint8_t bit_offset = 0;
    uint8_t value_mask = mask;
    while (!(value_mask & 1)) {
        value_mask >>= 1;
        bit_offset += 1;
    }
    uint8_t new_value = (existing_value & ~mask) | ((value & value_mask) << bit_offset);
    set_register(channel >= 3, ym_addr, new_value);
}

void Ym2612::set_register(uint8_t part, uint8_t ym_addr, uint8_t value)
{
    this->registers[part][ym_addr - YM_REG_FIRST_ADDR] = value;
    write_register(part, ym_addr, value);
}
uint8_t Ym2612::get_register(uint8_t part, uint8_t ym_addr)
{
    return this->registers[part][ym_addr - YM_REG_FIRST_ADDR];
}


/*
 * ym2612 communication
 */


void Ym2612::reset()
{
    digitalWriteFast(this->pin_ic, LOW);
    delay(10);
    digitalWriteFast(this->pin_ic, HIGH);
    delay(10);
}

void Ym2612::write_data(uint8_t data) {
    //set cs low to write d0..d7
    digitalWriteFast(this->pin_cs, LOW);

    //ouput bits to data pins
    for (int i=0; i < 8; i++) {
        digitalWriteFast(this->pin_data[i], (data >> i) & 1);
    }
    delayMicroseconds(1);

    // togle write pin
    digitalWriteFast(this->pin_wr, LOW);
    delayMicroseconds(5);
    digitalWriteFast(this->pin_wr, HIGH);
    delayMicroseconds(5);

    // reset cs
    digitalWriteFast(this->pin_cs, HIGH);
}

// part=0 channels 1-3
// part=1 channels 4-6
void Ym2612::write_register(uint8_t part, uint8_t reg, uint8_t data) 
{
    digitalWriteFast(this->pin_a1, part ? HIGH : LOW);
    delayMicroseconds(10);
    digitalWriteFast(this->pin_a0, LOW);
    write_data(reg);
    delayMicroseconds(10);
    digitalWriteFast(this->pin_a0, HIGH);
    write_data(data);
    delayMicroseconds(20);
}




/*
 * sega test program from docs
 */

void Ym2612::grandPianoVoice(uint8_t channel)
{
    enableLfo(false);
    setCh3Mode(0);
    for (int i=0; i < 6; i++) {
        keyOff(i);
    }
    enableDac(false);

    setDetune(channel, 0, 7);
    setDetune(channel, 1, 0);
    setDetune(channel, 2, 3);
    setDetune(channel, 3, 0);

    setMultiple(channel, 0, 1);
    setMultiple(channel, 1, 0xD);
    setMultiple(channel, 2, 3);
    setMultiple(channel, 3, 1);

    setTotalLevel(channel,0, 0x23);
    setTotalLevel(channel,1, 0x2D);
    setTotalLevel(channel,2, 0x26);
    setTotalLevel(channel,3, 0x00);

    setRateScale(channel,0, 1);
    setRateScale(channel,1, 2);
    setRateScale(channel,2, 1);
    setRateScale(channel,3, 2);

    setAttackRate(channel,0, 31);
    setAttackRate(channel,1, 25);
    setAttackRate(channel,2, 31);
    setAttackRate(channel,3, 20);

    setDecayRate(channel,0, 5);
    setDecayRate(channel,1, 5);
    setDecayRate(channel,2, 5);
    setDecayRate(channel,3, 7);

    setSustainRate(channel,0, 2);
    setSustainRate(channel,1, 2);
    setSustainRate(channel,2, 2);
    setSustainRate(channel,3, 2);

    setSustainLevel(channel,0, 0x1);
    setSustainLevel(channel,1, 0x1);
    setSustainLevel(channel,2, 0x1);
    setSustainLevel(channel,3, 0xA);

    setReleaseRate(channel,0, 0x1);
    setReleaseRate(channel,1, 0x1);
    setReleaseRate(channel,2, 0x1);
    setReleaseRate(channel,3, 0x6);

    setAlgorithm(channel, 2); 
    setFeedback(channel, 6);
    setOutputs(channel, 3);
}

void Ym2612::segaDocTestProgram(bool play_test_note)
{
    write_register(0, 0x22, 0);          // lfo off
    write_register(0, 0x27, 0);          // ch3 mode

    write_register(0, 0x28, 0);          // all channels off
    write_register(0, 0x28, 1);
    write_register(0, 0x28, 2);          
    write_register(0, 0x28, 4);          // 3 gets skipped!
    write_register(0, 0x28, 5);
    write_register(0, 0x28, 6);

    write_register(0, 0x2B, 0);          // dac off

    write_register(0, 0x30, 0x71);       // DT1/MUL
    write_register(0, 0x34, 0x0D);
    write_register(0, 0x38, 0x33);
    write_register(0, 0x3C, 0x01);

    write_register(0, 0x40, 0x23);       // Total Level
    write_register(0, 0x44, 0x2D);
    write_register(0, 0x48, 0x26);
    write_register(0, 0x4C, 0x00);

    write_register(0, 0x50, 0x5F);       // RS/AR 
    write_register(0, 0x54, 0x99);
    write_register(0, 0x58, 0x5F);
    write_register(0, 0x5C, 0x94);

    write_register(0, 0x60, 0x05);       // AM/D1R
    write_register(0, 0x64, 0x05);
    write_register(0, 0x68, 0x05);
    write_register(0, 0x6C, 0x07);

    write_register(0, 0x70, 0x02);       // D2R
    write_register(0, 0x74, 0x02);
    write_register(0, 0x78, 0x02);
    write_register(0, 0x7C, 0x02);

    write_register(0, 0x80, 0x11);       // D1L/RR
    write_register(0, 0x84, 0x11);
    write_register(0, 0x88, 0x11);
    write_register(0, 0x8C, 0xA6);

    write_register(0, 0x90, 0x00);       // Proprietary
    write_register(0, 0x94, 0x00);
    write_register(0, 0x98, 0x00);
    write_register(0, 0x9C, 0x00);

    write_register(0, 0xB0, 0x32);      // Feedback/algorithm
    write_register(0, 0xB4, 0xC0);      // Both speakers on

    write_register(0, 0x28, 0x00);      // Key off

    write_register(0, 0xA4, 0x22);      // Set frequency
    write_register(0, 0xA0, 0x69);

    if (play_test_note) {
        write_register(0, 0x28, 0xF0);      // Key on
        delay(1000);
        write_register(0, 0x28, 0x00);      // Key off
    }
}

void Ym2612::segaDocTestProgramCh4(bool play_test_note)
{
    write_register(0, 0x22, 0);          // lfo off
    write_register(0, 0x27, 0);          // ch3 mode

    write_register(0, 0x28, 0);          // all channels off
    write_register(0, 0x28, 1);
    write_register(0, 0x28, 2);          
    write_register(0, 0x28, 4);          // 3 gets skipped!
    write_register(0, 0x28, 5);
    write_register(0, 0x28, 6);

    write_register(0, 0x2B, 0);          // dac off

    write_register(1, 0x30, 0x71);       // DT1/MUL
    write_register(1, 0x34, 0x0D);
    write_register(1, 0x38, 0x33);
    write_register(1, 0x3C, 0x01);

    write_register(1, 0x40, 0x23);       // Total Level
    write_register(1, 0x44, 0x2D);
    write_register(1, 0x48, 0x26);
    write_register(1, 0x4C, 0x00);

    write_register(1, 0x50, 0x5F);       // RS/AR 
    write_register(1, 0x54, 0x99);
    write_register(1, 0x58, 0x5F);
    write_register(1, 0x5C, 0x94);

    write_register(1, 0x60, 0x05);       // AM/D1R
    write_register(1, 0x64, 0x05);
    write_register(1, 0x68, 0x05);
    write_register(1, 0x6C, 0x07);

    write_register(1, 0x70, 0x02);       // D2R
    write_register(1, 0x74, 0x02);
    write_register(1, 0x78, 0x02);
    write_register(1, 0x7C, 0x02);

    write_register(1, 0x80, 0x11);       // D1L/RR
    write_register(1, 0x84, 0x11);
    write_register(1, 0x88, 0x11);
    write_register(1, 0x8C, 0xA6);

    write_register(1, 0x90, 0x00);       // Proprietary
    write_register(1, 0x94, 0x00);
    write_register(1, 0x98, 0x00);
    write_register(1, 0x9C, 0x00);

    write_register(1, 0xB0, 0x32);      // Feedback/algorithm
    write_register(1, 0xB4, 0xC0);      // Both speakers on

    write_register(0, 0x28, 0x00);      // Key off

    write_register(1, 0xA4, 0x22);      // Set frequency
    write_register(1, 0xA0, 0x69);

    if (play_test_note) {
        write_register(0, 0x28, 0xF4);      // Key on
        delay(1000);
        write_register(0, 0x28, 0x04);      // Key off
    }
}
