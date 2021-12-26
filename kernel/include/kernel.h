#ifndef __KERNEL_H_
#define __KERNEL_H_

#include <stdbool.h>
#include <stddef.h>

EXTERN_C bool check_A20line(void);
EXTERN_C void enable_A20line(void);

#endif //__KERNEL_H_
