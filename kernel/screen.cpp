#include "include/screen.h"
#include "include/stdio.h"

uint16_t* vga_buffer = (uint16_t*) VGA_ADDRESS;
uint8_t vga_w = 80;
uint8_t vga_h = 25;
uint8_t vga_x, vga_y;

uint16_t vga_entry(unsigned char ch) {
    uint16_t ax;
    uint8_t ah, al;

    ah = 0x1;
    ah <<= 4;
    ah |= 0xf;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void clear_vga_buffer(void) {
    for (uint32_t i = 0; i < VGA_SIZE; i++)
        vga_buffer[i] = vga_entry(0);
    vga_x = 0;
    vga_y = 0;
}

void init_vga(void) {
    stdout = new FILE;
    stdout->stream = new DmNSOS::vga_stream;
    clear_vga_buffer();
}

void checkln(void) {
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
    checkln();
}

void vga_putchar(char ch) {
    checkln();
    vga_buffer[vga_x + (vga_y * vga_w)] = vga_entry(ch);
    vga_x++;
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
    vga_nln();
}