#ifndef __STDLIB_H_
#define __STDLIB_H_

#include "stdint.h"

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;
static char *itoa_simple_helper(char *dest, int i);
char *itoa(char *dest, int i);
int atoi(char*);
int32_t abs(int32_t);
int64_t labs(int64_t);
//div_t div(int num, int denom); TODO:
//ldiv_t ldiv(long int num, long int denom); TODO:

#endif //__STDLIB_H_