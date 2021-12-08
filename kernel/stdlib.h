#ifndef STDLIB_H
#define STDLIB_H

#define VGA_ADDRESS 0xb8000
#define MEM_START ((void *) 0x2000000)
//#define MEM_SPACE 536870912
#define MEM_SPACE 1024
#define MEM_END MEM_START + MEM_SPACE

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long int64_t;
typedef unsigned long uint64_t;
typedef uint32_t size_t;

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

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

#endif //STDLIB_H