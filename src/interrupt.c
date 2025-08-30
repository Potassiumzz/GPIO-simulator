#include <stdio.h>
#include <traffic_light.h>

void *handle_interrupt(void *arg) {
  while (1) {
    getchar();
    toggle_yellow_light_mode();
    printf("toggle yellow loop\n");
  }
  return NULL;
}
