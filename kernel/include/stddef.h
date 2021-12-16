#ifndef __STDDEF_H_
#define __STDDEF_H_

#define offsetof(st, m) __builtin_offsetof(st, m)
#define container_of(ptr, type, member) ({const typeof(((type *)0)->member) *__mptr = (ptr);(type *)((char *)__mptr - offsetof(type, member));})

#define NULL 0
#define nullptr 0

#endif //__STDDEF_H_
