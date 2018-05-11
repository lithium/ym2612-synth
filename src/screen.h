#ifndef SCREEN_H
#define SCREEN_H

#include "config.h"

#include "UiScreen.h"
#include "screen/DemoScreen.h"
#include "screen/SplashScreen.h"
#include "screen/MainScreen.h"
#include "screen/VoiceSettingsDialog.h"


extern DemoScreen demo_screen;
extern SplashScreen splash_screen;
extern MainScreen main_screen;

extern VoiceSettingsDialog voice_settings_dialog;


#endif