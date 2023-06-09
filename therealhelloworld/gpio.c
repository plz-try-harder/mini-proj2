#include <stdint.h>
#define GPIOA_BASE 0x48000000

typedef struct
{
	uint32_t moder;
	uint32_t otyper;
	uint32_t ospeedr;
	uint32_t pupdr;
	uint32_t idr;
	uint32_t odr;
	uint32_t bsrr;
	uint32_t lckr;
	uint32_t afrl;
	uint32_t brr;

} GPIO;

static volatile GPIO * const gpioA = (GPIO *)GPIOA_BASE;

void gpio_enable_usart(void)
{
	gpioA->moder &= ~(0b11<<4); 
	gpioA->moder |= (0b10<<4);		// activate the AF mode for pin A2 
	gpioA->afrl &= ~(0b111<<8); 
	gpioA->afrl |= (0b111<<8);		// AF7 for USATR2 
	
	gpioA->ospeedr &= ~(0b11<<4); 
	gpioA->ospeedr |= (0b10<<4);	// set speed to high speed
	
}
