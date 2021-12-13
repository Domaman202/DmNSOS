#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"

#define VGA_ADDRESS 0xb8000

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;

void* memcpy(void* dst, const void* src, size_t count);
void* memset(void* dst, char value, size_t count);
static char *itoa_simple_helper(char *dest, int i);
char *itoa(char *dest, int i);
int32_t abs(int32_t);
int64_t labs(int64_t);
//div_t div(int num, int denom); TODO:
//ldiv_t ldiv(long int num, long int denom); TODO:

#endif //STDLIB_H