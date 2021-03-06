#include "MainScreen.h"

#include "screen.h"
#include "colors.h"

#include "icons.h"
#include <font_ComicSansMS.h>


#define operator_width 131
#define operator_height 87

#define op1_x 16
#define op1_y 34

#define op2_x 172
#define op2_y 34

#define op3_x 16
#define op3_y 142

#define op4_x 172
#define op4_y 142

MainScreen::MainScreen()
{


    ops[0].setBounds(op1_x,op1_y, operator_width,operator_height);
    ops[0].setActive(true);
    ops[0].op_number = 0;
    active_op = &ops[0];
    addWidget(&ops[0]);


    ops[1].setBounds(op2_x,op2_y, operator_width,operator_height);
    ops[1].op_number = 1;
    addWidget(&ops[1]);

    ops[2].setBounds(op3_x,op3_y, operator_width,operator_height);
    ops[2].op_number = 2;
    addWidget(&ops[2]);

    ops[3].setBounds(op4_x,op4_y, operator_width,operator_height);
    ops[3].op_number = 3;
    addWidget(&ops[3]);

}

void MainScreen::start() 
{
    for (int i=0; i < children.size(); i++) {
        children.get(i)->setDirty(true);
    }
    encoders[0]._pulses_per_detent = 1;
}
void MainScreen::stop() 
{
    encoders[0]._pulses_per_detent = 4;
}


void MainScreen::paint()
{
    tft.fillScreen(COLOR_lightgrey);
    draw_icon(6,6, ICON_feedback);

    paintPatchName(nullptr,false);
    

    // force update all widgets with current patch
    memset(&last_patch, 0, sizeof(last_patch));
    settingsChanged(nullptr,-1,-1); 

    repaint(true);
}


struct icon_placement_t {
    int x;
    int y;
    int icon_number;
};
const struct icon_placement_t algorithm0[] = {
    {151, 76, ICON_arrow_right},
    {151,122, ICON_arrow_downleft},
    {151,184, ICON_arrow_right},
    {238,229, ICON_output},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm1[] = {
    { 78,121, ICON_arrow_down},
    {151,122, ICON_arrow_downleft},
    {151,184, ICON_arrow_right},
    {238,229, ICON_output},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm2[] = {
    {151,122, ICON_arrow_downleft},
    {151,122, ICON_arrow_downright},
    {151,184, ICON_arrow_right},
    {238,229, ICON_output},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm3[] = {
    {151, 76, ICON_arrow_right},
    {238,122, ICON_arrow_down},
    {151,184, ICON_arrow_right},
    {238,229, ICON_output},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm4[] = {
    { 78,121, ICON_arrow_down},
    {238,122, ICON_arrow_down},
    { 77,229, ICON_output},
    {238,229, ICON_output},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm5[] = {
    {151, 76, ICON_arrow_right},
    { 78,121, ICON_arrow_down},
    {151,122, ICON_arrow_downright},
    {238,122, ICON_output},
    { 77,229, ICON_output},
    {238,229, ICON_output},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm6[] = {
    {238,122, ICON_output},
    { 77,229, ICON_output},
    {238,229, ICON_output},
    {151, 76, ICON_arrow_right},
    {-1,-1,-1}
};
const struct icon_placement_t algorithm7[] = {
    { 77,122, ICON_output},
    {238,122, ICON_output},
    { 77,229, ICON_output},
    {238,229, ICON_output},
    {-1,-1,-1}
};

const struct icon_placement_t *algorithm_icon_placements[] = {
    algorithm0,
    algorithm1,
    algorithm2,
    algorithm3,
    algorithm4,
    algorithm5,
    algorithm6,
    algorithm7
};

void MainScreen::paintAlgorithm(uint8_t algorithm, bool erase)
{
    const icon_placement_t *placements = algorithm_icon_placements[algorithm];

    while (placements->x != -1) {
        if (erase) {
            erase_icon(placements->x, placements->y, placements->icon_number, COLOR_lightgrey);
        }
        else {
            draw_icon(placements->x, placements->y, placements->icon_number);
        }

        placements += 1;
    }
}
void MainScreen::paintFeedback(uint8_t feedback, bool erase)
{
    tft.setFont(ComicSansMS_14);
    tft.setCursor(15,9);
    tft.setTextColor(erase ? COLOR_black : COLOR_white);
    tft.print(feedback);
}
void MainScreen::paintPatchName(char *name, bool erase)
{

    tft.setFont(ComicSansMS_14);
    tft.setCursor(52,9);
    tft.setTextColor(erase ? COLOR_lightgrey : COLOR_white);

    auto l = name != nullptr ? strlen(name) : 0;
    if (l < 1) {
        tft.print("New Patch - to16");
    } else {
        tft.print(name);
    }
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

    SynthVoice *voice = synth.getActiveVoice();


    switch (enc)
    {
        case 0: {
            int tl = voice->getTotalLevel(op);
            direction *= -1;
            if ((tl+direction > 127) || (tl+direction < 0)) {
                return;
            }
            voice->setTotalLevel(op, tl + direction);
            break;
        }

        case 1: {
            int sl = voice->getSustainLevel(op);
            direction *= -1;
            if ((sl+direction > 15) || (sl+direction < 0)) {
                return;
            }
            voice->setSustainLevel(op, sl + direction);
            break;
        }

        case 2: {
            int ar = voice->getAttackRate(op);
            direction *= -1;
            if ((ar+direction > 31) || (ar+direction <= 0)) {
                return;
            }
            voice->setAttackRate(op, ar+direction);
            break;
        }
        case 3: {
            int dr = voice->getDecayRate(op);
            direction *= -1;
            if ((dr+direction > 31) || (dr+direction < 0)) {
                return;
            }
            voice->setDecayRate(op, dr + direction);
            break;
        }
        case 4: {
            int sr = voice->getSustainRate(op);
            direction *= -1;
            if ((sr+direction > 31) || (sr+direction < 0)) {
                return;
            }
            voice->setSustainRate(op, sr + direction);
            break;
        }
        case 5: {
            int rr = voice->getReleaseRate(op);
            direction *= -1;
            if (rr == 0) {
                if (direction > 0 )
                    return;
            }
            else
            if ((rr+direction > 16) || (rr+direction <= 0)) {
                return;
            }
            voice->setReleaseRate(op, rr + direction);
            break;
        }
        case 6: {

            const uint8_t detune_values[] = {
                0b111, //-3
                0b110, //-2
                0b101, //-1
                0b000, //0
                0b001, //+1
                0b010, //+2
                0b011, //+3
            };

            int dt = voice->getDetune(op);

            int cur_idx = -1;
            for (int i=0; i < 7; i++) {
                if (detune_values[i] == dt) {
                    cur_idx = i;
                    break;
                }
            }
            if (cur_idx == -1) {
                cur_idx = 3; // +0
            }

            if ((cur_idx + direction > 6) || (cur_idx+direction < 0)) {
                return;
            }

            voice->setDetune(op, detune_values[cur_idx + direction]);
            break;
        }
        case 7: {
            int mul = voice->getMultiple(op);
            if ((mul+direction > 15) || (mul+direction < 0)) {
                return;
            }
            voice->setMultiple(op, mul + direction);
            break;
        }
    }
}

void MainScreen::settingsChanged(Ym2612 *ym, uint8_t chan, uint8_t oper) 
{
    SynthVoice *voice = synth.getActiveVoice();
    struct ym2612_patch_t new_patch;
    voice->dumpPatch(&new_patch);


    if (chan == 255 || (last_patch.algorithm != new_patch.algorithm)) {
        paintAlgorithm(last_patch.algorithm, true);
        paintAlgorithm(new_patch.algorithm, false);
    }

    if (chan == 255 || last_patch.feedback != new_patch.feedback) {
        paintFeedback(last_patch.feedback, true);
        paintFeedback(new_patch.feedback, false);
    }

    if (strncmp(last_patch.name, new_patch.name, PATCH_NAME_LENGTH) != 0) {
        paintPatchName(last_patch.name, true);
        paintPatchName(new_patch.name, false);
    }

    for (auto i=0; i < 4; i++) {
        ops[i].operatorChanged(new_patch.op[i]);
    }


    last_patch = new_patch;
    repaint();
}

void MainScreen::buttonPressed(Button *b)
{
    Serial.print("press "); Serial.println(b->number);
    switch (b->number) {
        case 0:
            UiScreen::setActiveScreen(&voice_settings_dialog);
            break;
        case 1:
            UiScreen::setActiveScreen(&lfo_settings_dialog);
            break;
        case 2:
            UiScreen::setActiveScreen(&patch_dialog);
            break;
    }

}
