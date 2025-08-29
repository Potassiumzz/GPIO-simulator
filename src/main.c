#include "traffic_light.h"
#include <gpio.h>
#include <stdint.h>
#include <unistd.h>

int main() {
  uint8_t PORTA = 0x00;
  gpio_pin_status(PORTA);      // prints 00000000
  traffic_light_cycle(&PORTA); // traffic light FSM demo
  return 0;
}
