#ifndef WIDGET_H
#define WIDGET_H

#include "UiScreen.h"


class Widget
{
public:
    Widget();

    virtual void paint() = 0;
    bool isDirty();
    void setDirty(bool dirty = true);

    void setBounds(int x, int y, int w, int h);

    int x, y, w, h;

private:
    bool _dirty;
};



#endif