#ifndef __NEW_H_
#define __NEW_H_

extern "C" {
#include "alloc.h"
}

void* operator new (size_t count);
void* operator new[] (size_t count);
void* operator new (size_t count, void* ptr);
void operator delete (void* ptr);
void operator delete(void* ptr, size_t size);

#endif //__NEW_H_