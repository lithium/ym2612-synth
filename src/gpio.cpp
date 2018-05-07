#include "gpio.h"

#include <SPI.h>



#define ENC1_GPIO_A 9
#define ENC1_GPIO_B 10
TotalLevelEncoder enc1(ENC1_GPIO_A, ENC1_GPIO_B);


static volatile bool _gpio_ready = false;
static uint16_t _gpio_last = 0;


void handle_gpio_interrupt()    // ISR
{
    _gpio_ready = true;
}


void setup_gpio()
{
    pinMode(IO_CS, OUTPUT);
    pinMode(IO_IRQ, INPUT_PULLUP);

    SPI.begin();


    // setup iocon
    gpio_write_byte(IOCONA, 0b01000001);   // bank=0 mirror=ON seqop=ON intCC=INTCAP
    gpio_write_byte(IOCONB, 0b01000001);   // bank=0 mirror=ON seqop=ON intCC=INTCAP

    uint16_t t = gpio_read_word(IOCON);
    Serial.print("iocon: ");
    Serial.println(t, BIN);

    // all pins inputs
    gpio_write_word(IODIR, 0xFFFF);

    // all pins pullup
    gpio_write_word(GPPU, 0xFFFF);


    // setup interrupt
    gpio_write_word(GPINTEN, 0xFFFF);  // enable interrupt for all pins
    // gpio_write_word(DEFVAL, 0xFFFF); // default value is everything pulled up
    gpio_write_word(INTCON, 0x0000);  


    uint16_t v = gpio_read_word(GPIOA);
    Serial.print("v: ");
    Serial.println(v, BIN);
    attachInterrupt(digitalPinToInterrupt(IO_IRQ), handle_gpio_interrupt, CHANGE);

}



void check_encoders()
{
    if (_gpio_ready) {
        _gpio_ready = false;
        uint16_t capture = gpio_read_word(INTCAP);
        if (capture != _gpio_last) {
            Serial.print("gpio: ");
            Serial.println(capture, BIN);
            _gpio_last = capture;

            enc1.handle(capture);
        }
    }
}



void gpio_write_byte(int address, uint8_t value) 
{
    digitalWriteFast(IO_CS, LOW);

    SPI.transfer(WRITE_OPCODE);
    SPI.transfer(address);
    SPI.transfer(value);

    digitalWriteFast(IO_CS, HIGH);
}
void gpio_write_word(int address, uint16_t value)
{
    digitalWriteFast(IO_CS, LOW);

    SPI.transfer(WRITE_OPCODE);
    SPI.transfer(address);
    SPI.transfer((value >> 8) & 0xFF);
    SPI.transfer(value & 0xFF);

    digitalWriteFast(IO_CS, HIGH);
}


uint8_t gpio_read_byte(int address)
{
    digitalWriteFast(IO_CS, LOW);

    SPI.transfer(READ_OPCODE);
    SPI.transfer(address);
    uint8_t value = SPI.transfer(0);

    digitalWriteFast(IO_CS, HIGH);
    return value;
}
uint16_t gpio_read_word(int address)
{
    digitalWriteFast(IO_CS, LOW);

    SPI.transfer(READ_OPCODE);
    SPI.transfer(address);

    uint16_t value = SPI.transfer(0)<<8;
    value |= SPI.transfer(0);

    digitalWriteFast(IO_CS, HIGH);
    return value;
}

