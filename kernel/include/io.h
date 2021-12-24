#ifndef __IO_H_
#define __IO_H_

#include <stdint.h>

uint8_t read_port(uint16_t port);
void write_port(uint16_t port, uint8_t data);
void play_sound(uint32_t nFrequency);

#define outportb(port, value) asm("outb %b0, %w1"::"a"(value),"d"(port));
#define outportw(port, value) asm("outw %w0, %w1"::"a"(value),"d"(port));
#define outportl(port, value) asm("outl %0, %w1"::"a"(value),"d"(port));

#define inportb(port, out_value) asm("inb %w1, %b0":"=a"(value):"d"(port));
#define inportw(port, out_value) asm("inw %w1, %w0":"=a"(value):"d"(port));
#define inportl(port, out_value) asm("inl %w1, %0":"=a"(value):"d"(port));

void msleep(uint32_t millis); // TODO:

#endif //__IO_H_