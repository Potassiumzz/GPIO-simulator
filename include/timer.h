#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

struct Timer {
  uint16_t seconds; // can store upto 65,535 seconds which is about 18.2 hours, enough for most cases.
};

extern struct Timer timer0;

void *cpu_timer(void *arg);
void wait_sec(uint16_t seconds);

#endif
