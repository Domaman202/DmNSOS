#ifndef __STDIO_H_
#define __STDIO_H_

#include "stdint.h"
#include "stddef.h"

#define EOF -1

#define FILENAME_MAX 255
#define PATH_MAX 255
#define MAX_PATH 255
#define L_tmpnam sizeof("/tmp/") + 12

#define FOPEN_MAX 2048 / sizeof(struct FILE)

#define BUFSIZ 8192 * sizeof(int32_t)

#undef NULL
#define NULL (void*) nullptr

#ifndef __cplusplus
#include "alloc.h"
typedef struct FILE FILE;
#else
extern "C" {
#include "alloc.h"
}

class _FILE {
public:
    virtual int getc() = 0;
    virtual int putc(int c) = 0;
};

class __FILE : public _FILE {
public:
    char* buf;
    int32_t size;
    int32_t offset;

    virtual int getc() override {
        if (offset == size)
            return EOF;
        return buf[offset++];
    }

    virtual int putc(int c) override {
        if (offset == size)
            return buf[size] = EOF;
        return buf[offset++] = c;
    }
};

struct FILE {
    _FILE* file;
};

#endif //__cplusplus

EXTERN_C int fgetc(FILE *stream);
EXTERN_C int fputc(int c, FILE *stream);
EXTERN_C void setbuf(FILE *stream, char *buf);

#endif //__STDIO_H_