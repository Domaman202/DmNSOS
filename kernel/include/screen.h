#ifndef SCREEN_H
#define SCREEN_H

#include "stdlib.h"

#define VGA_SIZE vga_w * vga_h

extern uint16_t* vga_buffer;
extern uint8_t vga_w;
extern uint8_t vga_h;
extern uint32_t vga_index, next_line_index;

uint16_t vga_entry(unsigned char ch);
void clear_vga_buffer(uint16_t **buffer);
void init_vga(void);
void println();
void print_char(char ch);
void print_string(char *str);
void println_string(char *str);

#endif //SCREEN_H