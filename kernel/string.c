#include "inc/string.h"
#include "inc/alloc.h"

void* memcpy(void* dst, const void* src, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = ((char*) src)[count];
    return dst;
}

void* memmove(void *dest, const void *src, size_t len) {
    char *d = dest;
    const char *s = src;
    if (d < s)
        while (len--)
            *d++ = *s++;
    else {
        char *lasts = s + (len - 1);
        char *lastd = d + (len - 1);
        while (len--)
            *lastd-- = *lasts--;
    }
    return dest;
}

void* memset(void* dst, char value, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = value;
    return dst;
}

void byte_swap(uint8_t *data, int len) {
    int i;
    uint8_t temp;
    for(i = 0; i < len; i += 2) {
        temp = data[i];
        data[i] = data[i+1];
        data[i+1] = temp;
    }
}

char* strcpy(char *dest, const char *src) {
    return memcpy(dest, src, strlen(src) + 1);
}

char* strncpy(char *dest, const char *src, size_t n) {
    return memcpy(dest, src, n);
}

size_t strlen(const char *str){
    register const char *s;

    for (s = str; *s; ++s);
    return(s - str);
}


int strcmp(const char *p1, const char *p2) {
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}

void* memchr(const void* src_void, int c, size_t length) {
    const unsigned char *src = (const unsigned char*) src_void;

    while (length-- > 0) {
        if (*src == c)
            return (void*) src;
        src++;
    }
    return 0;
}