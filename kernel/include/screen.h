#ifndef __SCREEN_H_
#define __SCREEN_H_

#include <stdint.h>
#include <stddef.h>

#define VGA_SIZE vga_w * vga_h

extern uint16_t* vga_buffer;
extern uint8_t vga_w, vga_h, vga_x, vga_y;

EXTERN_C_START
uint16_t vga_entry(unsigned char);
void clear_vga_buffer(void);
void init_vga(void);
void checkln(void);
void vga_nln(void);
void print_char(char);
void print_string(char*);
void println_string(char*);
EXTERN_C_END

#endif //__SCREEN_H_