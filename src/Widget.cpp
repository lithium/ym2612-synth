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
    this->setDirty(true);
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

void Widget::repaint(bool force)
{
    int l = children.size();
    for (int i=0; i < l; i++) {
        Widget *w = children.get(i);
        if (force || w->isDirty()) {
            w->paint();
            w->setDirty(false);
        }
    }
}

Widget *Widget::getChildAtPoint(TS_Point p)
{
    int l = children.size();
    int x = ((double)p.x/4096.0) * SCREEN_WIDTH;
    int y = ((double)p.y/4096.0) * SCREEN_HEIGHT;
    for (int i=0; i < l; i++) {
        Widget *w = children.get(i);
        if (x >= w->x && x <= w->x+w->w && y >= w->y && y <= w->y+w->h) {
            return w;
        }
    }
    return nullptr;
}
