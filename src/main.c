#include <gpio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <traffic_light.h>
#include <unistd.h>

uint8_t PORTA = 0x00;

void *handle_interrupt(void *arg) {
  while (1) {
    getchar();
    toggle_yellow_light_mode();
    printf("toggle yellow loop\n");
  }
  return NULL;
}

void *traffic_light_fsm(void *arg) {
  uint8_t *port = (uint8_t *)arg;
  while (1) {
    traffic_light_cycle(port);
  }
  return NULL;
}

int main() {
  pthread_t fsm_thread, isr_thread;
  pthread_create(&isr_thread, NULL, handle_interrupt, NULL);
  pthread_create(&fsm_thread, NULL, traffic_light_fsm, &PORTA);

  pthread_join(fsm_thread, NULL);
  pthread_join(isr_thread, NULL);

  return 0;
}
