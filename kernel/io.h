#ifndef IO_H
#define IO_H

#include "stdlib.h"

uint8_t read_port(uint16_t port) {
    unsigned char data;
    asm("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}

void write_port(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : :"a" (data), "d" (port));
}

#define outportb(port, value) asm("outb %b0, %w1"::"a"(value),"d"(port));
#define outportw(port, value) asm("outw %w0, %w1"::"a"(value),"d"(port));
#define outportl(port, value) asm("outl %0, %w1"::"a"(value),"d"(port));

#define inportb(port, out_value) asm("inb %w1, %b0":"=a"(value):"d"(port));
#define inportw(port, out_value) asm("inw %w1, %w0":"=a"(value):"d"(port));
#define inportl(port, out_value) asm("inl %w1, %0":"=a"(value):"d"(port));

void play_sound(uint32_t nFrequency) {
    if (nFrequency == 0) {
        char tmp = (read_port(0x61) & 0xFC);
        write_port(0x61, tmp);
        return;
    }
    int Div;
    char tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / nFrequency;
    write_port(0x43, 0xb6);
    write_port(0x42, (uint8_t) (Div));
    write_port(0x42, (uint8_t) (Div >> 8));

    //And play the sound using the PC speaker
    tmp = read_port(0x61);
    if (tmp != (tmp | 3))
        write_port(0x61, tmp | 3);
}

#endif //IO_H