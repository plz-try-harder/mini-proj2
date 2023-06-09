#include "usart.h"
#include "gpio.h"
#include "rcc.h"

void usart_init(void) {
	rcc_enable_usart();
	
	
	gpio_enable_usart();
	
}


int _start(void) {
usart_init();
while(1) 
	{
	 usart_puts("Test\n");
	usart_putx(0xDEADBEEF);
	usart_putc('\n');
	}
}
