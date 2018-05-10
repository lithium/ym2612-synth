#include "MainScreen.h"

MainScreen::MainScreen()
{
    auto title_height = 20;
    auto padding = 2;
    auto operator_width = (320 - padding*3) / 2;
    auto operator_height = (240 - (title_height+padding) - padding*3) / 2;
    // auto operator_width = 30;
    // auto operator_height = 30;

    auto origin_y = title_height+padding*2;
    auto origin_x = padding;

    ops[0].setBounds(origin_x,origin_y, operator_width,operator_height);
    ops[0].setActive(true);
    addWidget(&ops[0]);

    ops[1].setBounds(origin_x + operator_width + padding, origin_y, operator_width,operator_height);
    addWidget(&ops[1]);

    ops[2].setBounds(origin_x, origin_y + operator_height+padding, operator_width,operator_height);
    addWidget(&ops[2]);

    ops[3].setBounds(origin_x + operator_width+padding,origin_y + operator_height+padding, operator_width,operator_height);
    addWidget(&ops[3]);

}


void MainScreen::paint()
{
    tft.fillScreen(ILI9341_BLACK);
    repaint();
}