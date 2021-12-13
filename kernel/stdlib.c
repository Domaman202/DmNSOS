#include "stdlib.h"

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

static char *itoa_simple_helper(char *dest, int i) {
    if (i <= -10) {
        dest = itoa_simple_helper(dest, i/10);
    }
    *dest++ = '0' - i%10;
    return dest;
}

char *itoa(char *dest, int i) {
    char *s = dest;
    if (i < 0) {
        *s++ = '-';
    } else {
        i = -i;
    }
    *itoa_simple_helper(s, i) = '\0';
    return dest;
}

int32_t abs(int32_t n) {
    return n < 0 ? n * -1 : n;
}

int64_t labs(int64_t n) {
    return n < 0 ? n * -1 : n;
}