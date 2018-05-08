
#include "DemoScreen.h"
#include "gpio.h"
#include "screen.h"

    auto width = 40;
    auto height = 20;
    auto padding = 2;

#define num_demos 8
DemoWidget demos[num_demos];

DemoScreen::DemoScreen()
{
    auto x = 110;
    auto y = 20;

    for (int i=0; i < 8; i++) {
        demos[i].setBounds(x, y, width, height);
        addWidget(&demos[i]);

        y += height+padding;
    }

}

void DemoScreen::paint()
{
    Serial.println("paint it ");
    tft.fillScreen(ILI9341_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);

    auto x = 20;
    auto y = 20;

    for (int i=0; i < 8; i++) {
        tft.setCursor(x,y);
        tft.print("ENC #");
        tft.print(i+1);
        tft.print(": ");
        y += height+padding;
    }
    repaint();
}

void DemoScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    int enc = get_encoder_number(e);
    Serial.print("encoder #");
    Serial.print(enc+1);
    Serial.print(" turned ");
    Serial.println(direction == 1 ? "right" : "left");

    DemoWidget *dw = &demos[enc];
    dw->counter += direction;
    dw->setDirty(true);
    repaint();
}




void DemoWidget::paint() {
    tft.fillRect(x, y, w, h, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(x, y);
    tft.print(counter);
}