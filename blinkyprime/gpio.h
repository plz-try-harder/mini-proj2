#ifndef THEREALHELLOWORLD_GPIO_H
#define THEREALHELLOWORLD_GPIO_H
#include <stdint.h>

void gpio_enable_usart(void);
void gpio_enable_led(void);
void gpio_led_on(void);
void led_set(int value);

#endif
