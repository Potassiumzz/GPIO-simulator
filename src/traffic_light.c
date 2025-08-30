#include <gpio.h>
#include <stdint.h>
#include <stdio.h>
#include <traffic_light.h>
#include <unistd.h>

enum TRAFFIC_LIGHTS { RED = 1, YELLOW = 2, RED_YELLOW = 3, GREEN = 4, GREEN_YELLOW = 6 };

struct TrafficLightFlags {
  uint8_t yellow_light_mode;
};

static struct TrafficLightFlags flags = {0};

/*
 * Toggle between yellow light flashing forever or making the traffic light cycle continue as normal.
 * Toggles the 5th GPIO pin, which is supposed to make the yellow light flash forever (make the 2nd pin's
 * state on).
 * */
void toggle_yellow_light_mode() { flags.yellow_light_mode = !flags.yellow_light_mode; }

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
      light = RED_YELLOW;
      break;
    case YELLOW:
      printf("YELLOW ");
      gpio_pin_set(port, 1);
      gpio_pin_toggle(port, 5);
      gpio_pin_status(*port);
      while (flags.yellow_light_mode) {
      }
      gpio_pin_toggle(port, 5);
      light = RED;
      break;
    case RED_YELLOW:
      printf("YELLOW + RED ");
      gpio_pin_set(port, 1);
      gpio_pin_status(*port);
      sleep(2);
      light = GREEN;
      gpio_pin_clear(port, 0); // turn off the red light
      break;
    case GREEN:
      printf("GREEN ");
      gpio_pin_clear(port, 1); // turn off the yellow light
      gpio_pin_set(port, 2);
      gpio_pin_status(*port);
      sleep(2);
      if (flags.yellow_light_mode) {
        gpio_pin_clear(port, 2); // turn off the green light before switching to yellow
        light = YELLOW;
      } else {
        light = GREEN_YELLOW;
      }
      break;
    case GREEN_YELLOW:
      printf("YELLOW + GREEN ");
      gpio_pin_set(port, 1);
      gpio_pin_status(*port);
      sleep(2);
      light = RED;
      gpio_pin_clear(port, 2); // turn off the green light
      break;
    }
  }
}
