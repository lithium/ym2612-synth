#ifndef SCREEN_H
#define SCREEN_H

#include "config.h"

#include "UiScreen.h"
#include "screen/DemoScreen.h"
#include "screen/SplashScreen.h"

extern UiScreen *active_screen;

extern DemoScreen demo_screen;
extern SplashScreen splash_screen;

void set_active_screen(UiScreen *screen);

#endif