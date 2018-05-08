#include "Widget.h"


Widget::Widget()
{
    setDirty(true);
}


void Widget::setBounds(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Widget::isDirty()
{
    return _dirty;
}
void Widget::setDirty(bool dirty)
{
    _dirty = dirty;
}
