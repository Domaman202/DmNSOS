#ifndef __SCREEN_H_
#define __SCREEN_H_

#include "stdlib.h"

#define VGA_SIZE vga_w * vga_h

extern uint16_t* vga_buffer;
extern uint8_t vga_w;
extern uint8_t vga_h;
extern uint16_t vga_x, vga_y;

uint16_t vga_entry(unsigned char ch);
void clear_vga_buffer(void);
void init_vga(void);
void println(void);
void print_char(char ch);
void print_string(char *str);
void println_string(char *str);

#endif //__SCREEN_H_