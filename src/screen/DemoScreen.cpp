
#include "DemoScreen.h"
#include "gpio.h"
#include "screen.h"

    auto width = 40;
    auto height = 20;
    auto padding = 2;

#define num_enc_demos ENCODER_COUNT
DemoWidget enc_demos[num_enc_demos];

DemoWidget btn_demos[BUTTON_COUNT];

DemoScreen::DemoScreen()
{
    auto x = 110;
    auto y = 20;
    for (int i=0; i < num_enc_demos; i++) {
        enc_demos[i].setBounds(x, y, width, height);
        addWidget(&enc_demos[i]);

        y += height+padding;
    }


    x = 240;
    y = 20;
    for (int i=0; i < BUTTON_COUNT; i++) {
        btn_demos[i].setBounds(x, y, width, height);
        addWidget(&btn_demos[i]);
        y += height + padding;
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
    for (int i=0; i < num_enc_demos; i++) {
        tft.setCursor(x,y);
        tft.print("ENC #");
        tft.print(i+1);
        tft.print(": ");
        y += height+padding;
    }

    x = 150;
    y = 20;
    for (int i=0; i < BUTTON_COUNT; i++) {
        tft.setCursor(x,y);
        tft.print("BTN #");
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

    DemoWidget *dw = &enc_demos[enc];
    dw->counter += direction;
    dw->setDirty(true);
    repaint();
}

void DemoScreen::buttonPressed(Button *b) 
{
    int btn = b->number;
    Serial.print("btn pressed #");
    Serial.print(btn+1);

    DemoWidget *dw = &btn_demos[btn % BUTTON_COUNT];
    dw->counter += 1;
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