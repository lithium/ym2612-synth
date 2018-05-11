#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "config.h"
#include "UiScreen.h"
#include "Widget.h"
#include <IntervalTimer.h>
#include "tft.h"

class SplashScreen : public UiScreen
{
public:
    SplashScreen();
    void paint() override;

    void start() override;
    void stop() override;
    void loop() override;

    void draw_logo(int color);
private:
    IntervalTimer _timer;

    int x, y;
    int xv, yv;

    int foreground, background;
    int width, height;


    

};

#endif
