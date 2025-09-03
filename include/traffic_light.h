#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <pthread.h>
#include <stdint.h>

struct TrafficLightFlags;

/*
 * Argument for 'pthread_create' function.
 * */
struct FSMThreadArg {
  uint8_t PORTA;
  pthread_mutex_t lock;
  pthread_cond_t cond;
};

void toggle_yellow_light_mode();
void *traffic_light_cycle(void *arg);

#endif
