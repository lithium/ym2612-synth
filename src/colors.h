#ifndef COLORS_H
#define COLORS_H

#include <inttypes.h>
#include <ILI9341_t3.h>





#define COLOR_black CL(0,0,0)
#define COLOR_white CL(0xFF,0xFF,0xFF)

#define COLOR_lightgrey CL(0xB3,0xB3,0xB3)
#define COLOR_midgrey CL(0x6D,0x6D,0x6D)
#define COLOR_darkgrey CL(0x41,0x40,0x42)

#define COLOR_cyan CL(0xB3,0xD6,0xB3)

#define COLOR_red CL(0xFF,0x00,0x00)



extern const uint16_t COLOR_emboss[];
extern const uint16_t COLOR_deboss[];

    
#endif