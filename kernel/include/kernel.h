#ifndef __KERNEL_H_
#define __KERNEL_H_

extern "C" {
#include "stdlib.h"
#include "stddef.h"
#include "setjmp.h"
#include "string.h"
#include "alloc.h"
#include "test.h"
#include "IDT.h"
#include "io.h"
}

#include "screen.h"
#include "stdio.h"
#include "new.h"

#endif //__KERNEL_H_