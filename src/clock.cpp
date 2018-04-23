#include "clock.h"


void start_clock()
{
    analogWriteFrequency(YM_CLK, MASTER_CLOCK_SPEED); 
    analogWriteResolution(8);
    analogWrite(YM_CLK, 128);
}

void stop_clock()
{
    analogWrite(YM_CLK, 0);
}


