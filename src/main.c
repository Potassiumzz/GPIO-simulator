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

void gpio_pin_set(uint8_t *port, uint8_t pin) { *port |= (1 << pin); }

int main() {
  uint8_t PORTA = 0x00;
  gpio_pin_status(PORTA);

  gpio_pin_set(&PORTA, 4);
  gpio_pin_set(&PORTA, 7);
  gpio_pin_status(PORTA); // prints 10010000

  return 0;
}
