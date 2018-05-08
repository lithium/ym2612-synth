
#include "DemoScreen.h"
#include "gpio.h"
#include "screen.h"

DemoScreen::DemoScreen()
{
    auto x = 40;
    auto y = 20;


    auto width = 40;
    auto height = 40;
    auto padding = 2;

    for (int i=0; i < 8; i++) {
        widgets[i].setBounds(x, y, width, height);
        y += height+padding;
    }


    // static paint
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);

    y = 20;
    x = 20;

    for (int i=0; i < 8; i++) {
        tft.setCursor(x,y);
        tft.print("ENC #");
        tft.print(i+1);
        tft.print(": ");
        y += 20;
    }

    setDirty(true); // paint widgets
}

void DemoScreen::paint()
{
    // for (int i=0; i < 8; i++) {
    //     if (widgets[i].isDirty()) {
    //         widgets[i].paint();
    //     }
    // }

    // Serial.println("paint it ");
    // tft.fillScreen(ILI9341_BLACK);

    // tft.setTextSize(2);
    // tft.setTextColor(ILI9341_WHITE);

    // auto x = 20;
    // auto y = 20;

    // for (int i=0; i < 8; i++) {
    //     tft.setCursor(x,y);
    //     tft.print("ENC #");
    //     tft.print(i+1);
    //     tft.print(": ");
    //     tft.print(counters[i]);
    //     y += 20;
    // }
}

void DemoScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    int enc = get_encoder_number(e);
    Serial.print("encoder #");
    Serial.print(enc+1);
    Serial.print(" turned ");
    Serial.println(direction == 1 ? "right" : "left");

    widgets[enc].counter += direction;
    widgets[enc].setDirty(true);
    // counters[enc] += direction;
    setDirty();
}




void DemoWidget::paint() {
    tft.fillRect(x, y, w, h, ILI9341_BLACK);
    tft.print(counter);
}