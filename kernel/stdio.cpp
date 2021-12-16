#include "include/stdio.h"

int fgetc(FILE *stream) {
    return stream->file->getc();
}

int fputc(int c, FILE *stream) {
    return stream->file->putc(c);
}

void setbuf(FILE *stream, char *buf) {
    __FILE* file = new __FILE;
    stream->file = file;
    file->buf = buf;
    file->size = BUFSIZ;
    file->offset = 0;
}