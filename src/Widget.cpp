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
void Widget::addWidget(Widget *w)
{
    children.add(w);
}

void Widget::repaint()
{
    int l = children.size();
    for (int i=0; i < l; i++) {
        Widget *w = children.get(i);
        if (w->isDirty()) {
            w->paint();
            w->setDirty(false);
        }
    }
}

