#include "inc/unistd.h"
#include "inc/stdlib.h"
#include "inc/IDT.h"

void sleep(uint32_t ticks) {
    uint32_t start = PITCounter;
    while (abs((int32_t)PITCounter - (int32_t)start) < ticks)
        asm volatile("nop");
}