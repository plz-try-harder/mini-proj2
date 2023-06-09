#include "usart.h"
#include "gpio.h"
#include "rcc.h"
#include "stk.h"

static volatile STK_TypeDef * const stk = STK;

void usart_init(void)
{
	rcc_enable_usart();
	rcc_enable_led();
	gpio_enable_usart();
	gpio_enable_led();
	usart_enable();
}

int _start(void)
{
	usart_init();
	systick_init();
	while(1)
	{
		__asm__ volatile ("WFI" : : : "memory");	
	}
}

void systick_init(void) {
	stk->ctrl = 0x0; 			// reset stk
	stk->ctrl |= (0b111<<0); 
	stk->load |= (0x1E8480-1<<0);
}
