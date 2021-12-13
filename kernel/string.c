#include "string.h"

void* memcpy(void* dst, const void* src, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = ((char*) src)[count];
    return dst;
}

void* memset(void* dst, char value, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = value;
    return dst;
}