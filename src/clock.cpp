#include "clock.h"


void start_clock()
{
    analogWriteFrequency(YM_CLK, 7670445); // 7.670445Mhz
    analogWriteResolution(8);
    analogWrite(YM_CLK, 128);
}

void stop_clock()
{
    analogWrite(YM_CLK, 0);
}


