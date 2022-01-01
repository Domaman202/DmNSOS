#include "inc/unistd.h"
#include "inc/IDT.h"

void sleep(uint32_t ticks) {
    uint32_t needed_tick = PITCounter + ticks;
    while (PITCounter < needed_tick) asm volatile("nop");
}