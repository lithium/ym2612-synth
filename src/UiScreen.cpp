
#include "UiScreen.h"



UiScreen demo_screen;

UiScreen *active_screen = NULL;


void set_active_screen(UiScreen *screen)
{
    active_screen = screen;
    for (int i=0; i < ENCODER_COUNT; i++) {
        encoders[i].setListener(active_screen);
    }
}




UiScreen::UiScreen()
{

}    

void UiScreen::encoderTurned(int direction, GpioEncoder *e) 
{
    int enc = get_encoder_number(e);
    Serial.print("encoder turned: ");
    Serial.print(direction);
    Serial.print(" @");
    Serial.println(enc, HEX);
}
