#include "MainScreen.h"

MainScreen::MainScreen()
{
    auto title_height = 20;
    auto padding = 20;
    // auto operator_width = (320 - padding*3) / 2;
    // auto operator_height = (240 - (title_height+padding) - padding*3) / 2;
    auto operator_width = 130;
    auto operator_height = 80;

    auto origin_y = title_height+padding*2;
    auto origin_x = padding;

    ops[0].setBounds(origin_x,origin_y, operator_width,operator_height);
    ops[0].setActive(true);
    ops[0].op_number = 0;
    active_op = &ops[0];
    addWidget(&ops[0]);

    ops[1].setBounds(origin_x + operator_width + padding, origin_y, operator_width,operator_height);
    ops[1].op_number = 1;
    addWidget(&ops[1]);

    ops[2].setBounds(origin_x, origin_y + operator_height+padding, operator_width,operator_height);
    ops[2].op_number = 2;
    addWidget(&ops[2]);

    ops[3].setBounds(origin_x + operator_width+padding,origin_y + operator_height+padding, operator_width,operator_height);
    ops[3].op_number = 3;
    addWidget(&ops[3]);

}


void MainScreen::paint()
{
    tft.fillScreen(ILI9341_BLACK);
    repaint();
}


void MainScreen::screenTouched(TS_Point p)
{
    OperatorWidget *touched_op = (OperatorWidget *)getChildAtPoint(p);
    if (!touched_op) {
        return;
    }

    if (active_op) {
        active_op->setActive(false);
    }
    touched_op->setActive(true);
    active_op = touched_op;

    repaint();
}

