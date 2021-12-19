#ifndef __STRING_H_
#define __STRING_H_

#include "stdint.h"

void* memcpy(void* dst, const void* src, size_t count);
void* memset(void* dst, char value, size_t count);

void byte_swap(uint8_t *data, int len);

#endif //__STRING_H_
