#include <Arduino.h>

void setup()
{
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    Serial.begin(38400);
    Serial.println("Hello ym2612");
}

void loop() 
{

}