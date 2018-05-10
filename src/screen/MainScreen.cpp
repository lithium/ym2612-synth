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

void MainScreen::start() 
{
    ym2612.addListener(this);
}
void MainScreen::stop() 
{
    ym2612.removeListener(this);
}

void MainScreen::paint()
{
    tft.fillScreen(ILI9341_BLACK);

    settingsChanged(-1,-1); // force update all operator widgets with current patch

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

void MainScreen::encoderTurned(int direction, GpioEncoder *e)
{
    int enc = get_encoder_number(e);
    int chan = active_channel;
    int op = active_op->op_number;
    switch (enc)
    {
        case 7:
            ym2612.setMultiple(chan, op, ym2612.getMultiple(chan, op) + direction);
            break;
        case 6:
            ym2612.setDetune(chan, op, ym2612.getDetune(chan, op) + direction);
            break;
    }
}

void MainScreen::settingsChanged(uint8_t chan, uint8_t oper) 
{
    struct ym2612_patch_t new_patch;

    ym2612.dumpPatch(active_channel, &new_patch);
    for (auto i=0; i < 4; i++) {
        ops[i].operatorChanged(new_patch.op[i]);
    }

    last_patch = new_patch;
    repaint();
}

