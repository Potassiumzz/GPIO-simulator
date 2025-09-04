#include "gpio.h"
#include <pthread.h>
#include <stdio.h>
#include <traffic_light.h>

void *handle_interrupt(void *arg) {
  struct FSMThreadArg *fsmThreadArg = (struct FSMThreadArg *)arg;
  while (1) {
    getchar();
    pthread_mutex_lock(&fsmThreadArg->lock);
    toggle_yellow_light_mode();
    pthread_cond_signal(&fsmThreadArg->cond);
    pthread_mutex_unlock(&fsmThreadArg->lock);
    gpio_pin_status(fsmThreadArg->PORTA);
    printf("toggle yellow loop\n");
  }
  return NULL;
}
