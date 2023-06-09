#include <stdint.h>
#define RCC_BASE 0x40021000

typedef struct
{
	uint32_t cr;
	uint32_t icsrc;
	uint32_t cfgr;
	uint32_t pllcfgr;
	uint32_t pllsai1cfgr;
	uint32_t unused1;
	uint32_t cier;
	uint32_t cifr;
	uint32_t cicr;
	uint32_t unused2;
	uint32_t ahb1rstr;
	uint32_t ahb2rstr;
	uint32_t ahb3rstr;
	uint32_t unused3;
	uint32_t apb1rstr1;
	uint32_t apb1rstr2;
	uint32_t apb2rstr;
	uint32_t unused4;
	uint32_t ahb1enr;
	uint32_t ahb2enr;
	uint32_t ahb3enr;
	uint32_t unused5;
	uint32_t apb1enr1;
	uint32_t apb1enr2;
	uint32_t apb2enr;
	uint32_t unused6;
	uint32_t ahb1smenr;
	uint32_t ahb2smenr;
	uint32_t ahb3smenr;
	uint32_t unused7;
	uint32_t apb1smenr1;
	uint32_t apb1smenr2;
	uint32_t apb2smenr;
	uint32_t unused8;
	uint32_t ccipr;
	uint32_t unused9;
	uint32_t bdcr;
	uint32_t csr;
	uint32_t crrcr;
	uint32_t ccipr2;
} RCC;


static volatile RCC * const rcc = (RCC *)RCC_BASE;

void rcc_enable_usart(void)
{
	rcc->apb1enr1 &= ~(1<<17);
	rcc->apb1enr1 |= (1<<17); 
	
	rcc->ahb2enr &= ~(1<<0);		// enable GPIOA Clock 
	rcc->ahb2enr |= (1<<0);
}

void rcc_enable_led(void)
{
	rcc->ahb2enr &= ~(1<<1);		// enable GPIOB Clock 
	rcc->ahb2enr |= (1<<1);
}
