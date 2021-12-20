#include "include/stdio.h"

FILE *stdout = nullptr;

void frmc(FILE *stream) {
    stream->stream->rmc();
}

int fgetc(FILE *stream) {
    return stream->stream->getc();
}

int fputc(int c, FILE *stream) {
    return stream->stream->putc(c);
}

void setbuf(FILE *file, char *buf) {
    DmNSOS::buf_stream* stream = new DmNSOS::buf_stream;
    file->stream = stream;
    stream->buf = buf;
    stream->size = BUFSIZ;
    stream->offset = 0;
}