#include <gpio.h>
#include <stdio.h>
#include <traffic_light.h>
#include <unistd.h>

enum TRAFFIC_LIGHTS { RED = 1, YELLOW = 2, GREEN = 4 };

void traffic_light_cycle(uint8_t *port) {

  enum TRAFFIC_LIGHTS light = RED;

  while (1) {
    switch (light) {
    case RED:
      printf("RED ");
      gpio_pin_set(port, 0);
      gpio_pin_clear(port, 1); // turn off the yellow light
      gpio_pin_status(*port);
      sleep(2);
      light = YELLOW;
      break;
    case YELLOW:
      printf("YELLOW ");
      gpio_pin_set(port, 1);
      gpio_pin_status(*port);
      if (*port == 0x06) {
        printf("YELLOW + GREEN ");
        light = RED;
        gpio_pin_clear(port, 2); // turn off the green light
      } else if (*port == 0x03) {
        printf("YELLOW + RED ");
        gpio_pin_status(*port);
        light = GREEN;
        gpio_pin_clear(port, 0); // turn off the red light
      }
      gpio_pin_status(*port);
      sleep(2);
      break;
    case GREEN:
      printf("GREEN ");
      gpio_pin_clear(port, 1); // turn off the yellow light
      gpio_pin_set(port, 2);
      gpio_pin_status(*port);
      sleep(2);
      light = YELLOW;
      break;
    }
  }
}
