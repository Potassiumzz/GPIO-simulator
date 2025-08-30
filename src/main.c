#include <gpio.h>
#include <interrupt.h>
#include <pthread.h>
#include <stdint.h>
#include <traffic_light.h>
#include <unistd.h>

uint8_t PORTA = 0x00;

int main() {
  pthread_t fsm_thread, isr_thread;
  pthread_create(&isr_thread, NULL, handle_interrupt, NULL);
  pthread_create(&fsm_thread, NULL, traffic_light_cycle, &PORTA);

  pthread_join(fsm_thread, NULL);
  pthread_join(isr_thread, NULL);

  return 0;
}
