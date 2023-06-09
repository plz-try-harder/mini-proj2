#include <stdio.h>
#include <stdint.h>
#include "usart.h"
#define USART2_BASE	0x40004400

///
/// name register
/// 
typedef struct 
{
	volatile uint32_t cr1;	// contol register 1, word lenght
	volatile uint32_t cr2;	// contol register 2, number of stopbits
	volatile uint32_t cr3;	// contol register 3, DMA register for multibuffer communication
	volatile uint32_t brr;	// baudrate register 
	volatile uint32_t gtpr;	// guard-time register
	volatile uint32_t rtor;	// resiver timeout register
	volatile uint32_t rqr;	// request register
	struct
	{
		unsigned int :6; 	// Bits [0,5]
		unsigned int tc:1; 	// Bit 6
		unsigned int txe:1; 	// Bit 7
		unsigned int :24; 	// Bits [8, 31]
	} isr;
	volatile uint32_t icr;	// clear flag register
	volatile uint32_t rdr;	// resive data register
	volatile uint32_t tdr;	// transmitt data register
} USART;


static volatile USART * const usart2 = (USART*) USART2_BASE;


void usart_putc(uint8_t c)
{
  while (!usart2->isr.txe);
  usart2->tdr = c;
  while (!usart2->isr.tc);
}

void usart_puts(const char *str)
{
	char c;
	while ((c = *str++))
	{
		usart_putc(c);
	}
}

void usart_putx(uint32_t val)
{
	for (int i = 1; i <= 8; i++) 
	{
    		uint8_t c = (val >> (32-i*4)) & 0xF;
    		c = ((c < 10) ? c + '0' : (c + 'A' - 10));
    		usart_putc(c);
	}
}

void usart_enable(void)
{
	usart2->cr1 = 0x00;		// set M-Bit to 8-Bit
	
	usart2->brr &= ~(0xFFF<<0); 
	usart2->brr |= (0x1A1<<0);	// set baudrate to 9600 wihle using 4Mhz
	
	usart2->cr1 &= ~(1<<3); 
	usart2->cr1 |= (1<<3);		// enable TE bit
	
	usart2->cr1 &= ~(1<<0); 
	usart2->cr1 |= (1<<0);		// finaly enable USART	
}

