#include "Label.h"


Label::Label(const char *label, ILI9341_t3_font_t font, int foreground, int background)
{
    setLabel(label);
    setFont(font);
    setColor(foreground, background);
}


void Label::paint()
{
    if (_label != nullptr) {
        paintLabel(_label, false);
    }
}

void Label::paintLabel(const char *label, bool erase)
{
    tft.setFont(_font);
    tft.setTextColor(erase ? _background : _foreground);
    tft.setCursor(x + padding_left, y + padding_top);
    tft.print(label);
}
