#ifndef STDLIB_H
#define STDLIB_H

#include "stddef.h"

#define VGA_ADDRESS 0xb8000

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

void* memcpy(void* dst, const void* src, size_t count);
void* memset(void* dst, char value, size_t count);
static char *itoa_simple_helper(char *dest, int i);
char *itoa(char *dest, int i);

#endif //STDLIB_H