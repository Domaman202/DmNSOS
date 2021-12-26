#ifndef __KERNEL_H_
#define __KERNEL_H_

#include <stdbool.h>

extern "C" bool check_A20(void);
extern "C" void enable_A20(void);

#endif //__KERNEL_H_
