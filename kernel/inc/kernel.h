#ifndef KERNEL_H
#define KERNEL_H

#include "setjmp.h"
#include "screen.h"
#include "string.h"
#include "unistd.h"
#include "alloc.h"
#include "IDT.h"
#include "io.h"

void program_memory(void);

#endif //KERNEL_H