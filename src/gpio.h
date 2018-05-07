#ifndef GPIO_H
#define GPIO_H

#include "config.h"
#include "Encoder.h"


#define WRITE_OPCODE 0b01000000
#define READ_OPCODE  0b01000001

// iocon.bank = 0
#define IODIR   0x00
#define IODIRA  0x00
#define IODIRB  0x01

#define IPOL    0x02
#define IPOLA   0x02
#define IPOLB   0x03

#define GPINTEN  0x04
#define GPINTENA 0x04
#define GPINTENB 0x05

#define DEFVAL  0x06
#define DEFVALA 0x06
#define DEFVALB 0x07

#define INTCON  0x08
#define INTCONA 0x08
#define INTCONB 0x09

#define IOCON   0x0A
#define IOCONA  0x0A
#define IOCONB  0x0B

#define GPPU    0x0C
#define GPPUA   0x0C
#define GPPUB   0x0D

#define INTF    0x0E
#define INTFA   0x0E
#define INTFB   0x0F

#define INTCAP  0x10
#define INTCAPA 0x10
#define INTCAPB 0x11

#define GPIO    0x12
#define GPIOA   0x12
#define GPIOB   0x13

#define OLAT    0x14
#define OLATA   0x14
#define OLATB   0x15

void gpio_write_byte(int address, uint8_t value);
void gpio_write_word(int address, uint16_t value);
uint8_t gpio_read_byte(int address);
uint16_t gpio_read_word(int address);





void setup_gpio();
void check_encoders();

#endif