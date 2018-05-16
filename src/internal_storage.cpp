#include "internal_storage.h"


InternalStorage internal_storage;


InternalStorage::InternalStorage()
{
}

uint InternalStorage::patch_addr(int number)
{
    return EEPROM_ADDR_PATCHES + (number * (PATCH_HEADER_SIZE + sizeof(struct ym2612_patch_t)));
}

void InternalStorage::scanPatches()
{
    struct ym2612_patch_t p;

    memset(patch_names, 0, sizeof(patch_names));

    for (auto i=0; i < INTERNAL_PATCH_MAX_COUNT; i++) {
        auto addr = patch_addr(i);
        auto header = EEPROM.read(addr);
        if (header == PATCH_HEADER_COOKIE) {
            // previously saved
            EEPROM.get(addr+PATCH_HEADER_SIZE, p);
            memcpy(patch_names[i], p.name, PATCH_NAME_LENGTH);
        }
    }
}

bool InternalStorage::readPatch(int number, struct ym2612_patch_t *dest)
{
    auto addr = patch_addr(number);
    auto header = EEPROM.read(addr);
    if (header == PATCH_HEADER_COOKIE) {
        EEPROM.get(addr+PATCH_HEADER_SIZE, *dest);
        return true;
    }
    return false;
}
bool InternalStorage::writePatch(int number, struct ym2612_patch_t *src)
{
    auto addr = patch_addr(number);
    EEPROM.update(addr, PATCH_HEADER_COOKIE);
    EEPROM.put(addr+PATCH_HEADER_SIZE, *src);
    return true;
}
