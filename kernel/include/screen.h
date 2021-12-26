#ifndef __SCREEN_H_
#define __SCREEN_H_

#include <stdint.h>
#include <stddef.h>

#define VGA_DEFAULT_COLOR 0x09

#define VGA_SIZE vga_w * vga_h

extern uint16_t* vga_buffer;
extern uint8_t vga_w, vga_h, vga_x, vga_y;

EXTERN_C_START
// vga utils
uint16_t vga_cc(unsigned char, uint8_t);
void vga_clear_buffer(void);
void vga_init(void);
void vga_checkln(void);
void vga_nln(void);
// cursor utils
void vga_enable_cursor(uint8_t start, uint8_t end);
void vga_disable_cursor();
void vga_set_cursor(uint16_t);
// TODO: move to stdio.h
void print_char(char);
void print_charc(char, uint8_t);
void print_string(char*);
void print_stringc(char*, uint8_t);
void println_string(char*);
void println_stringc(char*, uint8_t);
EXTERN_C_END

#endif //__SCREEN_H_
