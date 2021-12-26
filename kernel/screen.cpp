#include "include/screen.h"
#include <stdio.h>

extern "C" {
#include "include/io.h"
}

uint16_t* vga_buffer = (uint16_t*) VGA_ADDRESS;
uint8_t vga_w = 80;
uint8_t vga_h = 25;
uint8_t vga_x, vga_y;

// VGA

uint16_t vga_entry(unsigned char ch) {
    uint16_t ax;
    uint8_t ah, al;

    ah = 0x0;
    ah <<= 4;
    ah |= 0xC;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void vga_clear_buffer(void) {
    for (uint32_t i = 0; i < VGA_SIZE; i++)
        vga_buffer[i] = vga_entry(0);
    vga_x = 0;
    vga_y = 0;
}

void vga_init(void) {
    stdout = new FILE;
    stdout->stream = new DmNSOS::vga_stream;
    vga_clear_buffer();
    vga_set_cursor(0);
}

void vga_checkln(void) {
    if (vga_x > vga_w)
        vga_nln();
    if (vga_y == vga_h) {
        vga_x = 0;
        vga_y = vga_h - 1;
        for (uint16_t i = 1; i < vga_h; i++)
            for (uint16_t j = 0; j < vga_w; j++)
                vga_buffer[((i - 1) * vga_w) + j] = vga_buffer[(i * vga_w) + j];
        for (uint16_t i = 0; i < vga_w; i++)
            vga_buffer[(vga_w * (vga_h - 1)) + i] = vga_entry(0);
    }
}

void vga_nln(void) {
    vga_x = 0;
    vga_y++;
    vga_checkln();
}

// CURSOR

void vga_enable_cursor(uint8_t start, uint8_t end) {
	write_port(0x3D4, 0x0A);
	write_port(0x3D5, (read_port(0x3D5) & 0xC0) | start);
	write_port(0x3D4, 0x0B);
	write_port(0x3D5, (read_port(0x3D5) & 0xE0) | end);
}

void vga_disable_cursor() {
	write_port(0x3D4, 0x0A);
	write_port(0x3D5, 0x20);
}

void vga_set_cursor(uint16_t pos) {
	write_port(0x3D4, 0x0F);
	write_port(0x3D5, (uint8_t) (pos & 0xFF));
	write_port(0x3D4, 0x0E);
	write_port(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

// TODO: MOVE TO STDIO.CPP

void print_char(char c) {
    fputc(c, stdout);
}

void print_string(char *str) {
    uint32_t index = 0;
    while (str[index]) {
        fputc(str[index], stdout);
        index++;
    }
}

void println_string(char *str) {
    print_string(str);
    print_char('\n');
}
