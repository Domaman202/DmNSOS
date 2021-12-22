#include "mls.h"

void test(void) {
    mls_c();
}

void mls_c(void) {
    FILE *file = malloc(sizeof(FILE));
    char *str = malloc(BUFSIZ);
    setbuf(file, str);
    fputc('M', file);
    fputc('L', file);
    fputc('S', file);
    fputc('-', file);
    fputc('C', file);
    fputc('\0', file);
    println_string(str);
    fclose(file);
    free(file);
}