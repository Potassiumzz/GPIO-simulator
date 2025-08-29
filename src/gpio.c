#include <gpio.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Display the current status of the GPIO pins (8 bits) as individual bits.
 * 1 = on, 0 = off
 * */
void gpio_pin_status(uint8_t port) {
  char binary[8];
  for (uint8_t i = 0; i < 8; i++) {
    binary[(sizeof binary - sizeof binary[i]) - i] = (port >> i) & 0x01;
    // Check if all the bits were stored in the binary array, and print the result.
    if (i == 7) {
      for (i = 0; i < sizeof binary; i++) {
        printf("%d", binary[i]);
      }
      break;
    }
  }
  printf("\n");
}

/*
 * Set the value of a pin as on (make a bit one) where
 * @params *port is the address of a port (register)
 * @params pin is the pin (bit) that has to be set as one, starting from 0 to 7.
 * */
void gpio_pin_set(uint8_t *port, uint8_t pin) { *port |= (1 << pin); }

/*
 * Clear the value of a pin (make a bit zero) where
 * @params *port is the address of a port (register)
 * @params pin is the pin (bit) that has to be cleared, starting from 0 to 7.
 * */
void gpio_pin_clear(uint8_t *port, uint8_t pin) { *port &= ~(1 << pin); }

/*
 * Toggle the value of a pin where
 * @params *port is the address of a port (register)
 * @params pin is the pin (bit) that has to be toggled, starting from 0 to 7.
 * */
void gpio_pin_toggle(uint8_t *port, uint8_t pin) { *port ^= (1 << pin); }
