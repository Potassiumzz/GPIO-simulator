#include <gpio.h>
#include <interrupt.h>
#include <pthread.h>
#include <stdint.h>
#include <traffic_light.h>
#include <unistd.h>

int main() {
  pthread_t fsm_thread, isr_thread;
  struct FSMThreadArg fsmThreadArg = {.PORTA = 0x00};
  pthread_mutex_init(&fsmThreadArg.lock, NULL);
  pthread_cond_init(&fsmThreadArg.cond, NULL);

  pthread_create(&isr_thread, NULL, handle_interrupt, &fsmThreadArg);
  pthread_create(&fsm_thread, NULL, traffic_light_cycle, &fsmThreadArg);

  pthread_join(fsm_thread, NULL);
  pthread_join(isr_thread, NULL);

  pthread_mutex_destroy(&fsmThreadArg.lock);
  pthread_cond_destroy(&fsmThreadArg.cond);

  return 0;
}
