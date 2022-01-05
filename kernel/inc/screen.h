#ifndef SCREEN_H
#define SCREEN_H

#include "stdlib.h"

#define VGA_DEFAULT_COLOR 0x1E
#define VGA_SIZE vga_w * vga_h

extern uint16_t* vga_buffer;
extern uint8_t vga_w, vga_h, vga_x, vga_y, vga_auto_scroll;

// vga utils
uint16_t vga_cc(unsigned char, uint8_t);
void vga_clear_buffer(void);
void vga_init(void);
void vga_checkln(void);
// cursor utils
void vga_enable_cursor(uint8_t start, uint8_t end);
void vga_disable_cursor();
void vga_set_cursor(uint16_t);
// TODO: move to stdio.h
void remove_char(void);
void print_char(char);
void print_charc(char, uint8_t);
void print_string(char*);
void print_stringc(char*, uint8_t);
void println(void);
void println_string(char*);
void println_stringc(char*, uint8_t);
#endif //SCREEN_H