#ifndef PATCH_H
#define PATCH_H


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

#endif