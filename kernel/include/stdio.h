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
typedef struct FILE FILE;
#else
namespace DmNSOS {
    class file {
    public:
        virtual int getc() = 0;
        virtual int putc(int c) = 0;
    };

    class buf_file : public file {
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
}

struct FILE {
    DmNSOS::file* file;
};
#endif //__cplusplus

EXTERN_C_START
#include "alloc.h"

int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
void setbuf(FILE *stream, char *buf);
EXTERN_C_END

#endif //__STDIO_H_