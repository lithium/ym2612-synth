
#include "UiScreen.h"



UiScreen::UiScreen()
{

}    

void UiScreen::paint()
{

}

bool UiScreen::isDirty()
{
    return _dirty;
}
void UiScreen::setDirty(bool dirty)
{
    _dirty = dirty;
}
