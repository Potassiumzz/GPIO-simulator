#include <interrupt.h>
#include <stdint.h>
#include <time.h>
#include <timer.h>
#include <unistd.h>

static const uint8_t CPU_KHz = 2; // assuming our CPU is 2KHz for this simulation
static const uint8_t OCR = 250;   // Output Compare Register
static const uint8_t PRESCALER = 8;

struct Timer timer0 = {.seconds = 0};

void wait_sec(uint16_t seconds) {
  uint16_t time_to_reach = timer0.seconds + seconds;
  while (timer0.seconds < time_to_reach) {
  }
}

void *cpu_timer(void *arg) {
  /*
   * To learn about timespec and clock_nanosleep: https://linux.die.net/man/2/clock_nanosleep
   * To learn about clock_gettime: https://linux.die.net/man/2/clock_gettime
   * */
  struct timespec next;
  clock_gettime(CLOCK_MONOTONIC, &next);
  uint8_t prescaler_counter = 0;
  uint8_t timer = 0;
  uint16_t cycle_time_us = (1000000 / (CPU_KHz * 1000)); // should be 500(us) for 2KHz frequency
  while (1) {
    next.tv_nsec += cycle_time_us * 1000;
    while (next.tv_nsec >= 1000000000) {
      next.tv_nsec = 0;
      next.tv_sec++;
    }
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
    prescaler_counter++;
    if (prescaler_counter >= PRESCALER) {
      timer++;
      prescaler_counter = 0;
      if (timer == OCR) {
        timer = 0;
        timer_ISR();
      }
    }
  }
  return NULL;
}
