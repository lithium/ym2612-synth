
#include "UiScreen.h"

UiScreen::UiScreen()
{

}    

void UiScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    Serial.print("encoder turned: ");
    Serial.print(direction);
    Serial.print(" @");
    Serial.println((int)e, HEX);
}
