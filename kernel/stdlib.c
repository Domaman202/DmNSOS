#include "inc/stdlib.h"

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

int atoi(char* s) {
    int n = 0;
    while (*s >= '0' && *s <= '9') {
        n *= 10;
        n += *s++;
        n -= '0';
    }
    return n;
}

uint32_t abs(int32_t n) {
    return n < 0 ? n * -1 : n;
}

uint64_t labs(int64_t n) {
    return n < 0 ? n * -1 : n;
}

int rand() {
    static unsigned long int next = 1;
    next = next * 1103515245 + 12345;
    return (next / 65536) % 32768;
}