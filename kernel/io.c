#include "inc/io.h"

uint8_t read_port(uint16_t port) {
    unsigned char data;
    asm("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}

void write_port(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : :"a" (data), "d" (port));
}