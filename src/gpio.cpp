#include "gpio.h"

#include <SPI.h>
#include <IntervalTimer.h>

#define ENCODER_TIMER_PERIOD_USEC 500
static IntervalTimer _encoder_timer;


static int _encoder_gpio_pins[] = {
    9, 8,
    11, 10,
    13, 12,
    15, 14,
    1, 0,
    3, 2,
    5, 4,
    7, 6,
};
GpioEncoder encoders[ENCODER_COUNT];


static volatile bool _gpio_ready = false;
static uint16_t _gpio_last = 0;




static int _button_pins[] = {
    // A11, A10
    22, 23
};
Button buttons[BUTTON_COUNT];




void handle_gpio_interrupt()    // ISR
{
    _gpio_ready = true;

    for (int i=0; i < BUTTON_COUNT; i++) {
        buttons[i].tick();
    }
}

void setup_gpio()
{
    pinMode(IO_CS, OUTPUT);


    //setup encoders
    for (int i=0; i < ENCODER_COUNT; i++) {
        encoders[i].setup(_encoder_gpio_pins[i*2], _encoder_gpio_pins[i*2+1]);
    }

    //setup buttons
    for (int i=0; i < BUTTON_COUNT; i++) {
        buttons[i].setup(_button_pins[i]);
    }


    SPI.begin();


    // setup iocon
    gpio_write_byte(IOCONA, 0b01000000);   // bank=0 mirror=ON seqop=ON
    gpio_write_byte(IOCONB, 0b01000000);   // bank=0 mirror=ON seqop=ON

    // all pins inputs
    gpio_write_word(IODIR, 0xFFFF);

    // all pins pullup
    gpio_write_word(GPPU, 0xFFFF);


    _encoder_timer.begin(handle_gpio_interrupt, ENCODER_TIMER_PERIOD_USEC);

}



void check_inputs()
{
    if (_gpio_ready) {
        _gpio_ready = false;

        // check encoders
        uint16_t capture = gpio_read_word(GPIO);
        if (capture != _gpio_last) {
            _gpio_last = capture;

            for (int i=0; i < ENCODER_COUNT; i++) {
                encoders[i].handle(capture);
            }
        }

    }
    // check buttons
    for (int i=0; i < BUTTON_COUNT; i++) {
        buttons[i].firePending();
    }

}

int get_encoder_number(GpioEncoder *e)
{
    for (int i=0; i < ENCODER_COUNT; i++) {
        if (e == &encoders[i]) {
            return i;
        }
    }
    return -1;
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

