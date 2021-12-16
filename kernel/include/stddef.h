#ifndef __STDDEF_H_
#define __STDDEF_H_

#define offsetof(st, m) __builtin_offsetof(st, m)
#define container_of(ptr, type, member) ({const typeof(((type *)0)->member) *__mptr = (ptr);(type *)((char *)__mptr - offsetof(type, member));})

#define NULL 0
#define nullptr 0

#define VGA_ADDRESS 0xb8000

#ifndef __cplusplus
#define EXTERN_C
#define EXTERN_C_START
#define EXTERN_C_END
#else
#define EXTERN_C extern "C"
#define EXTERN_C_START EXTERN_C {
#define EXTERN_C_END }
#endif //__cplusplus

#define __cdecl __attribute__((__cdecl__))

#endif //__STDDEF_H_