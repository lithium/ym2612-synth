#ifndef INTERNAL_STORAGE_H
#define INTERNAL_STORAGE_H

#include "config.h"
#include "patch.h"
#include <EEPROM.h>


#define EEPROM_SIZE 2048

struct voice_storage_t {
    uint8_t voice_size; // size of record including this header

    uint8_t midi_channel=1;
    uint8_t note_lo=0;
    uint8_t note_hi=127;
    uint8_t midi_transpose=0;

    uint8_t name_len;
    char name[];

    uint8_t patch_path_len;
    char patch_path[];
};


#define PATCH_HEADER_COOKIE 0xA5
#define PATCH_HEADER_SIZE 1


#define INTERNAL_PATCH_MAX_COUNT 16
#define PATCH_STORAGE_SIZE PATCH_HEADER_SIZE + sizeof(struct ym2612_patch_t) * INTERNAL_PATCH_MAX_COUNT

#define INTERNAL_VOICE_MAX_COUNT 16
#define VOICE_STORAGE_SIZE sizeof(struct voice_storage_t) * INTERNAL_VOICE_MAX_COUNT



// eeprom addresses

#define EEPROM_ADDR_SETTINGS    0       // 100 bytes reserved for configuration
#define EEPROM_ADDR_PATCHES     100
#define EEPROM_ADDR_VOICES      (EEPROM_ADDR_PATCHES + PATCH_STORAGE_SIZE)

static_assert((EEPROM_ADDR_VOICES + VOICE_STORAGE_SIZE) < EEPROM_SIZE, "eeprom wont fit!");




class InternalStorage
{
public:
    InternalStorage();
    void scanPatches();

    bool readPatch(int number, struct ym2612_patch_t *dest);
    bool writePatch(int number, struct ym2612_patch_t *src);

    char patch_names[PATCH_NAME_LENGTH+1][INTERNAL_PATCH_MAX_COUNT];
private:
    uint patch_addr(int number);
};

extern InternalStorage internal_storage;

#endif
