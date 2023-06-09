#ifndef THEREALHELLOWORLD_USART_H
#define THEREALHELLOWORLD_USART_H
#include <stdint.h>

void usart_putc(uint8_t c);
void usart_puts(const char *str);
void usart_putx(uint32_t val);
void usart_enable(void);

#endif
