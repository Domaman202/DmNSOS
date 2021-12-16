#include "include/new.h"

void* operator new (size_t count) {
    return malloc(count);
}

void* operator new[] (size_t count) {
    return malloc(count);
}

void* operator new (size_t count, void* ptr) {
    return ptr;
}

void operator delete (void* ptr) noexcept {
    free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept {
    free(ptr);
}