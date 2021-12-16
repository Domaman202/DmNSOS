#ifndef __STDIO_H_
#define __STDIO_H_

/// INCLUDE

#include "stdint.h"
#include "stddef.h"

EXTERN_C_START
#include "screen.h"
#include "alloc.h"
EXTERN_C_END

/// CONSTANTS

#define EOF -1

#define FILENAME_MAX 255
#define PATH_MAX 255
#define MAX_PATH 255
#define L_tmpnam sizeof("/tmp/") + 12

#define FOPEN_MAX 2048 / sizeof(struct FILE)

#define BUFSIZ 8192 * sizeof(int32_t)

#undef NULL
#define NULL (void*) nullptr

/// CLASSES AND STRUCTURES

#ifndef __cplusplus
typedef struct FILE FILE;
#else
namespace DmNSOS {
    class stream {
    public:
        virtual int getc() = 0;
        virtual int putc(int c) = 0;
    };

    class buf_stream : public stream {
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

    class vga_stream : public stream {
    public:
        virtual int getc() override {
            return EOF; // TODO: implement
        }

        virtual int putc(int c) override {
            vga_putchar((char) c);
            return c;
        }
    };
}

struct FILE {
    DmNSOS::stream* stream;
};
#endif //__cplusplus

/// VARIABLES

extern FILE* stdout;

/// FUNCTIONS

EXTERN_C_START
int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
void setbuf(FILE *stream, char *buf);
EXTERN_C_END

#endif //__STDIO_H_