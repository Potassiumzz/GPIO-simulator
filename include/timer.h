#ifndef TIMER_H
#define TIMER_H

#include <pthread.h>
#include <stdint.h>

struct Timer {
  uint16_t seconds; // can store upto 65,535 seconds which is about 18.2 hours, enough for most cases.
};

struct TimerThread {
  pthread_mutex_t timer_lock;
  pthread_cond_t timer_cond;
};

extern struct Timer timer0;
extern struct TimerThread timer0_thread;

void *cpu_timer(void *arg);
void wait_sec(uint16_t seconds);

#endif
