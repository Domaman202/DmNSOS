#ifndef STRING_H
#define STRING_H

#include "stdint.h"

#define NULL 0

void* memcpy(void* dst, const void* src, size_t count);
void* memmove(void *dest, const void *src, size_t len);
void* memset(void* dst, char value, size_t count);

void byte_swap(uint8_t *data, int len);

size_t strlen(const char* str);
char* strcpy(char *dest, const char *src);
char* strncpy(char *dest, const char *src, size_t n);
int strcmp(const char *p1, const char *p2);
char* appendCharToCharArray(char* array, char a);
void* memchr(const void* src_void, int c, size_t length);

#endif //STRING_H
