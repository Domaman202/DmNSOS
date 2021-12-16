#ifndef __KERNEL_H_
#define __KERNEL_H_

extern "C" {
#include "setjmp.h"
#include "screen.h"
#include "alloc.h"
#include "ahci.h"
#include "IDT.h"
#include "io.h"
}

#endif //__KERNEL_H_