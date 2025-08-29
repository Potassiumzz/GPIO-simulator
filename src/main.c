#include <gpio.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

enum TRAFFIC_LIGHTS { RED = 1, YELLOW = 2, GREEN = 4 };

int main() {
  uint8_t PORTA = 0x00;
  gpio_pin_status(PORTA); // prints 00000000
  enum TRAFFIC_LIGHTS light = RED;

  while (1) {
    switch (light) {
    case RED:
      printf("RED ");
      gpio_pin_set(&PORTA, 0);
      gpio_pin_clear(&PORTA, 1); // turn off the yellow light
      gpio_pin_status(PORTA);
      sleep(2);
      light = YELLOW;
      break;
    case YELLOW:
      printf("YELLOW ");
      gpio_pin_set(&PORTA, 1);
      gpio_pin_status(PORTA);
      if (PORTA == 0x06) {
        printf("YELLOW + GREEN ");
        light = RED;
        gpio_pin_clear(&PORTA, 2); // turn off the green light
      } else if (PORTA == 0x03) {
        printf("YELLOW + RED ");
        gpio_pin_status(PORTA);
        light = GREEN;
        gpio_pin_clear(&PORTA, 0); // turn off the red light
      }
      gpio_pin_status(PORTA);
      sleep(2);
      break;
    case GREEN:
      printf("GREEN ");
      gpio_pin_clear(&PORTA, 1); // turn off the yellow light
      gpio_pin_set(&PORTA, 2);
      gpio_pin_status(PORTA);
      sleep(2);
      light = YELLOW;
      break;
    }
  }

  return 0;
}
