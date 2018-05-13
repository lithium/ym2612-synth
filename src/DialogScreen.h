#ifndef DIALOG_SCREEN_H
#define DIALOG_SCREEN_H

#include "config.h"
#include "UiScreen.h"
#include "tft.h"


class DialogScreen:
        public UiScreen
{
public:
    DialogScreen();

    virtual void paint() override;

};

#endif
