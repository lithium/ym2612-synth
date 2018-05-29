#ifndef LABEL_H
#define LABEL_H


#include "config.h"
#include "Widget.h"
#include "tft.h"
#include "colors.h"


class Label : public Widget
{
public:
    Label(const char *label = nullptr, ILI9341_t3_font_t font = ComicSansMS_14, int foreground=COLOR_white, int background=COLOR_lightgrey);

    void paint() override;
    void paintLabel(const char *label, bool erase);

    void setLabel(const char *label)
    {
        if (_label) {
            paintLabel(_label, true);
        }
        _label = label;
        setDirty(true);
    }
    const char *getLabel() { return _label; }

    void setFont(ILI9341_t3_font_t font) {
        _font = font;
    }
    void setColor(int foreground, int background) {
        _foreground = foreground;
        _background = background;
    }


    int padding_left = 0;
    int padding_top = 0;
private:
    const char *_label = nullptr;
    ILI9341_t3_font_t _font = ComicSansMS_14;
    uint16_t _foreground = COLOR_white;
    uint16_t _background = COLOR_lightgrey;
};



#endif
