#include "inc/io.h"

uint8_t read_port(uint16_t port) {
    unsigned char data;
    asm("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}

void write_port(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : :"a" (data), "d" (port));
}

void play_sound(uint32_t nFrequence) {
    uint32_t Div;
    uint8_t tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / nFrequence;
    write_port(0x43, 0xb6);
    write_port(0x42, (uint8_t) (Div) );
    write_port(0x42, (uint8_t) (Div >> 8));

    //And play the sound using the PC speaker
    tmp = read_port(0x61);
    if (tmp != (tmp | 3)) {
        write_port(0x61, tmp | 3);
    }
}

void nosound() {
    uint8_t tmp = read_port(0x61) & 0xFC;
    write_port(0x61, tmp);
}
