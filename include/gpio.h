#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void gpio_pin_status(uint8_t port);
void gpio_pin_set(uint8_t *port, uint8_t pin);
void gpio_pin_clear(uint8_t *port, uint8_t pin);
void gpio_pin_toggle(uint8_t *port, uint8_t pin);
#endif
