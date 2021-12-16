#ifndef __SCREEN_H_
#define __SCREEN_H_

#include "stdlib.h"
#include "stddef.h"

#define VGA_SIZE vga_w * vga_h

extern uint16_t* vga_buffer;
extern uint8_t vga_w, vga_h, vga_x, vga_y;

EXTERN_C_START
uint16_t vga_entry(unsigned char ch);
void clear_vga_buffer(void);
void init_vga(void);
void checkln(void);
void vga_nln(void);
void vga_putchar(char ch);
void print_string(char *str);
void println_string(char *str);
EXTERN_C_END

#endif //__SCREEN_H_