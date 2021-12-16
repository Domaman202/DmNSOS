#include "include/test.h"

void test(void) {
    FILE* file;
    char* str = malloc(80);
    setbuf(file, str);
    fputc('H', file);
    fputc('e', file);
    fputc('l', file);
    fputc('l', file);
    fputc('o', file);
    fputc(',', file);
    fputc(' ', file);
    fputc('W', file);
    fputc('o', file);
    fputc('r', file);
    fputc('l', file);
    fputc('d', file);
    fputc('!', file);
    fputc('\0', file);
    println_string(str);
    free(str);
    free(file);
}