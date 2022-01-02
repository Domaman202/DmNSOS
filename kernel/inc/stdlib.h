#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

static char *itoa_simple_helper(char *dest, int i);
char *itoa(char *dest, int i);

int atoi(char*);

uint32_t abs(int32_t);
uint64_t labs(int64_t);

int rand(void);

#endif //STDLIB_H