#ifndef __KERNEL_H_
#define __KERNEL_H_

extern "C" {
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <alloc.h>
#include "IDT.h"
#include "io.h"
}

#include "../../std/stddef.h"
#include "screen.h"
#include "../../std/stdio.h"
#include "../../std/new.h"

#endif //__KERNEL_H_