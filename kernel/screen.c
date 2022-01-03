#include "inc/screen.h"
#include "inc/stddef.h"
#include "inc/IDT.h"
#include "inc/io.h"

uint16_t* vga_buffer = (uint16_t*) VGA_ADDRESS;
uint8_t vga_w = 80;
uint8_t vga_h = 25;
uint8_t vga_x, vga_y, vga_auto_scroll = 1;

uint16_t __attribute__((gnu_inline)) vga_cc(register unsigned char ch, register uint8_t c) {
    uint16_t ax;

    ax = c;
    ax <<= 8;
    ax |= ch;

    return ax;
}

void vga_clear_buffer(void) {
    for (uint32_t i = 0; i < VGA_SIZE; i++)
        vga_buffer[i] = vga_cc(0, VGA_DEFAULT_COLOR);
    vga_x = 0;
    vga_y = 0;
}

void vga_init(void) {
    vga_clear_buffer();
    vga_set_cursor(0);
}

void vga_checkln(void) {
    if (vga_x > vga_w)
        println();
    if (vga_y == vga_h) {
        if (!vga_auto_scroll)
            getchar();
        vga_x = 0;
        vga_y = vga_h - 1;
        for (uint8_t i = 1; i < vga_h; i++)
            for (uint8_t j = 0; j < vga_w; j++)
                vga_buffer[((i - 1) * vga_w) + j] = vga_buffer[(i * vga_w) + j];
        for (uint8_t i = 0; i < vga_w; i++)
            vga_buffer[(vga_w * (vga_h - 1)) + i] = vga_cc(0, VGA_DEFAULT_COLOR);
    }
}

void println(void) {
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

// TODO: MOVE TO STDIO.C

void remove_char(void) {
    vga_x--;
    if (vga_x < 0) {
        vga_x = 0;
        vga_y--;
    }
    uint16_t pos = vga_x + (vga_y * vga_w);
    vga_buffer[pos] = vga_cc(0, VGA_DEFAULT_COLOR);
    vga_set_cursor(pos);
}

void print_char(char c) {
    print_charc(c, VGA_DEFAULT_COLOR);
}

void print_charc(char ch, uint8_t c) {
    if (ch == '\n') {
        println();
        return '\n';
    }
    vga_checkln();
    uint16_t pos = vga_x + (vga_y * vga_w);
    vga_buffer[pos] = vga_cc(ch, c);
    vga_set_cursor(pos + 1);
    vga_x++;
}

void print_string(char *str) {
    uint32_t index = 0;
    while (str[index]) {
        print_char(str[index]);
        index++;
    }
}

void print_stringc(char *str, uint8_t c) {
    uint32_t index = 0;
    while (str[index]) {
        print_charc(str[index], c);
        index++;
    }
}

void println_string(char *str) {
    print_string(str);
    println();
}

void println_stringc(char *str, uint8_t c) {
    print_stringc(str, c);
    println();
}