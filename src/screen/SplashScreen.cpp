#include "SplashScreen.h"
#include "screen.h"

static bool _tick = false;
static bool _holding = false;
static int _hold_counter = 0;
static int _hold_compare = 30000;
auto animation_interval = 80000;

SplashScreen::SplashScreen()
{
    background = ILI9341_BLUE;
    foreground = ILI9341_WHITE;

    width = 180;
    height = 39;    
}

void SplashScreen::paint()
{
    tft.fillScreen(background);
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(2, 2);
    tft.print(VERSION_STRING);
}

void splash_screen_tick()
{
    _tick = true;
}

void SplashScreen::draw_logo(int color)
{
    tft.setTextSize(3);
    tft.setTextColor(color);
    tft.setCursor(x,y);
    tft.print("Opie N.2");
}

void SplashScreen::loop()
{
    if (!_tick) return;

    if (_holding) {
        if (++_hold_counter > _hold_compare) {
            UiScreen::setActiveScreen(&demo_screen);
        }
    } else {
        draw_logo(background);
        x += xv;
        y += yv;

        if ((y <= 0) || (y + height >= 240)) {
            yv *= -1;

            // reached bottom hold
            _holding = true;
        }
        if ((x <= 0) || (x + width >= 320)) {
            xv *= -1;
        }


        draw_logo(foreground);
        _tick = false;
    }
}

void SplashScreen::start()
{
    x = 0;
    y = 20;
    xv = 20;
    yv = 20;

    _timer.begin(splash_screen_tick, animation_interval);
}

void SplashScreen::stop()
{
    _timer.end();
}

