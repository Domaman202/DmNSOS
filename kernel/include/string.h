#ifndef __STRING_H_
#define __STRING_H_

#include "stdint.h"

void* memcpy(void* dst, const void* src, size_t count);
void* memset(void* dst, char value, size_t count);

void byte_swap(uint8_t *data, int len);

size_t strlen(const char* str);
char* strcpy(char *dest, const char *src);
int strcmp(const char *p1, const char *p2);
char* appendCharToCharArray(char* array, char a);

#endif //__STRING_H_
