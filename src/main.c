#include <stdint.h>
#include <stdio.h>

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

int main() {
  uint8_t PORTA = 0x00;
  gpio_pin_status(PORTA);

  return 0;
}
