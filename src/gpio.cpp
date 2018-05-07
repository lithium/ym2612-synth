#include "gpio.h"

// mcp23s18 gpio;

#define MAX_CHECKS 10
static uint16_t _encoder_state[MAX_CHECKS];
static uint8_t _encoder_state_idx = 0;
static uint16_t _encoders_debounced = 0;


#define ENCODER_TIMER_PERIOD_USEC 5000
static IntervalTimer _encoder_timer;


#define ENC1_GPIO_A 0
#define ENC1_GPIO_B 1
TotalLevelEncoder enc1(ENC1_GPIO_A, ENC1_GPIO_B);


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

void handle_gpio_interrupt();

void setup_gpio()
{
    pinMode(IO_CS, OUTPUT);
    pinMode(IO_IRQ, INPUT_PULLUP);

    SPI.begin();


    // setup iocon
    gpio_write_byte(IOCONA, 0b01000000);   // bank=0 mirror=ON seqop=ON
    gpio_write_byte(IOCONB, 0b01000000);   // bank=0 mirror=ON seqop=ON

    uint16_t t = gpio_read_word(IOCON);
    Serial.print("iocon: ");
    Serial.println(t, BIN);

    // all pins inputs
    gpio_write_word(IODIR, 0xFFFF);

    // all pins pullup
    gpio_write_word(GPPU, 0xFFFF);


    // setup interrupt
    // gpio_write_word(GPINTEN, 0xFFFF);  // enable interrupt for all pins
    // gpio_write_word(DEFVAL, 0xFFFF); // default value is everything pulled up
    // gpio_write_word(INTCON, 0xFFFF);  


    uint16_t v = gpio_read_word(GPIOA);
    Serial.print("v: ");
    Serial.println(v, BIN);
    // attachInterrupt(digitalPinToInterrupt(IO_IRQ), handle_gpio_interrupt, CHANGE);


    // uint8_t a = gpio_read_byte(GPIOA);
    // Serial.print("a: ");
    // Serial.println(a, HEX);
    // uint8_t b = gpio_read_byte(GPIOB);
    // Serial.print("b: ");
    // Serial.println(b, HEX);


    // gpio.postSetup(IO_CS);
    // gpio.begin();
    // gpio.portPullup(HIGH);
    // gpio.gpioPinMode(INPUT);


    // initialize encoder debouncing
    memset(_encoder_state, 0, sizeof(_encoder_state));
    _encoder_state_idx = 0;
    _encoder_timer.begin(encoder_irq, ENCODER_TIMER_PERIOD_USEC);

    v = gpio_read_word(GPIOA);
    Serial.print("v: ");
    Serial.println(v, BIN);
    // enc1 = TotalLevelEncoder(ENC1_GPIO_A, ENC1_GPIO_B);
    // enc2 = GpioEncoder(ENC2_GPIO_A, ENC2_GPIO_B);
    // enc3 = GpioEncoder(ENC3_GPIO_A, ENC3_GPIO_B);
    // enc4 = GpioEncoder(ENC4_GPIO_A, ENC4_GPIO_B);
    // enc5 = GpioEncoder(ENC5_GPIO_A, ENC5_GPIO_B);
    // enc6 = GpioEncoder(ENC6_GPIO_A, ENC6_GPIO_B);
    // enc7 = GpioEncoder(ENC7_GPIO_A, ENC7_GPIO_B);
    // enc8 = GpioEncoder(ENC8_GPIO_A, ENC8_GPIO_B);
}


static volatile bool _gpio_ready = false;

void handle_gpio_interrupt()    // ISR
{
    _gpio_ready = true;
    // digitalWriteFast(PIN_LED, HIGH);
}

static uint16_t last = 0;

void check_encoders()
{
    if (_gpio_ready) {
        _gpio_ready = false;
        uint16_t port = gpio_read_word(GPIO);
        if (port != last) {
            Serial.print("gpio: ");
            Serial.println(port, BIN);
            last = port;
        }
    }
    // static uint16_t last = 12;
    // // uint16_t port = gpio.readGpioPort();
    // uint16_t port = gpio_read_word(GPIOA);
    // if (port != last) {
    //     Serial.print("gpio: ");
    //     Serial.println(port, HEX);
    //     last = port ;
    // }

    // uint16_t s = encoder_debounced_state();
    // enc1.handle(s);
}




void encoder_irq()
{
    _gpio_ready = true;
    // uint16_t raw_key_pressed = gpio.readGpioPortFast();

    // _encoder_state[_encoder_state_idx] = raw_key_pressed;
    // _encoder_state_idx = (_encoder_state_idx+1) % MAX_CHECKS;

    // digitalWriteFast(PIN_LED, !digitalReadFast(PIN_LED));
}

uint16_t encoder_debounced_state()
{
    uint16_t j = 0xffff;

    for(int i=0; i < MAX_CHECKS-1; i++) {
        j &= _encoder_state[i];
    }
    _encoders_debounced = _encoders_debounced ^ j;
    return _encoders_debounced;
}





// #define MAX_CHECKS 10   // # checks before a switch is debounced
// uint8_t Debounced_State;    // Debounced state of the switches
// uint8_t State[MAX_CHECKS];  // Array that maintains bounce status
// uint8_t Index;  // Pointer into State
// // Service routine called by a timer interrupt
// void DebounceSwitch3()
// {
//     uint8_t i,j;
//     State[Index]=RawKeyPressed();
//     ++Index;
//     j=0xff;
//     for(i=0; i<MAX_CHECKS-1;i++)j=j & State[i];
//     Debounced_State=Debounced_State ^ j;
//     if(Index>=MAX_CHECKS)Index=0;
// }