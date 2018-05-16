#ifndef PATCH_H
#define PATCH_H

#include <inttypes.h>

#define PATCH_NAME_LENGTH 16

struct tfi_patch_t {
    uint8_t algorithm;
    uint8_t feedback;
    struct {
        uint8_t multiplier;
        uint8_t detune;
        uint8_t total_level;
        uint8_t rate_scale;
        uint8_t attack_rate;
        uint8_t decay_rate;
        uint8_t sustain_rate;
        uint8_t release_rate;
        uint8_t sustain_level;
        uint8_t ssg_eg;
    } op[4];
};



struct ym2612_patch_op_t {
    uint8_t multiplier;
    uint8_t detune;
    uint8_t total_level;
    uint8_t rate_scale;
    uint8_t attack_rate;
    uint8_t decay_rate;
    uint8_t sustain_rate;
    uint8_t release_rate;
    uint8_t sustain_level;
    uint8_t lfo_enabled;
    uint16_t frequency;
};
struct ym2612_patch_t {
    uint8_t algorithm;
    uint8_t feedback;
    bool lfo_enabled;
    uint8_t lfo_frequency;
    uint8_t lfo_am_depth;
    uint8_t lfo_fm_depth;
    struct ym2612_patch_op_t op[4];
    uint8_t category;
    char name[PATCH_NAME_LENGTH];
    uint8_t terminator; // should always be 0
};

#endif