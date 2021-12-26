#ifndef __STDIO_H_
#define __STDIO_H_

/// INCLUDE

#include "stdint.h"
#include "stddef.h"

EXTERN_C_START
#include "../kernel/include/screen.h"
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
typedef struct {
  void* stream;
} FILE;
#else
namespace DmNSOS {
class stream {
public:
	virtual int fclose() = 0;
	virtual void rmc(void) = 0;
	virtual int getc(void) = 0;
	virtual int putc(int) = 0;
	virtual int putc(int, uint8_t c) = 0;
};

class buf_stream: public stream {
public:
	char *buf;
	int32_t size;
	int32_t offset;

	virtual int fclose(void) override {
		free(this);
		free(buf);
		return 0;
	}

	virtual void rmc(void) override {
		buf[offset] = EOF;
		offset--;
	}

	virtual int getc(void) override {
		if (offset == size)
			return EOF;
		return buf[offset++];
	}

	virtual int putc(int c) override {
		if (offset == size)
			return buf[size] = EOF;
		return buf[offset++] = c;
	}

	virtual int putc(int c, uint8_t ch) override {
		return EOF;
	}
};

class vga_stream: public stream {
public:
	virtual int fclose(void) override {
		return EOF;
	}

	virtual void rmc(void) override {
		vga_x--;
		if (vga_x < 0) {
			vga_x = 0;
			vga_y--;
		}
		uint16_t pos = vga_x + (vga_y * vga_w);
		vga_buffer[pos] = vga_cc(0, VGA_DEFAULT_COLOR);
		vga_set_cursor(pos);
	}

	virtual int getc() override {
		return EOF; // TODO: implement
	}

	virtual int putc(int c) override {
		return putc(c, 0x0C);
	}

	virtual int putc(int ch, uint8_t c) override {
		if (ch == '\n') {
			vga_nln();
			return '\n';
		}
		vga_checkln();
		uint16_t pos = vga_x + (vga_y * vga_w);
		vga_buffer[pos] = vga_cc(ch, c);
		vga_set_cursor(pos + 1);
		vga_x++;
		return ch;
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
int fclose(FILE*);
void frmc(FILE*);
int fgetc(FILE*);
int fputc(int, FILE*);
int fputcc(int, uint8_t c, FILE *stream);
void setbuf(FILE *stream, char *buf);
EXTERN_C_END

#endif //__STDIO_H_
