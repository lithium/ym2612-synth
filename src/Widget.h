#ifndef WIDGET_H
#define WIDGET_H

#include <LinkedList.h>

class Widget;


class Widget
{
public:
    Widget();

    virtual void paint() = 0;  // expensive full repaint
    void repaint(); // repaint dirty widgets

    bool isDirty();
    void setDirty(bool dirty = true);

    void setBounds(int x, int y, int w, int h);
    void addWidget(Widget *child);


    // public members
    int x, y, w, h;
    LinkedList<Widget *> children;


private:
    bool _dirty;

};



#endif