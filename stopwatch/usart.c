#include <stdio.h>
#include <stdint.h>
#include "bithelper.h"

#define USART2_BASE 0x40004400

#define ISR_TXE (1<<7)
#define ISR_TC  (1<<6)

typedef struct
{
    uint32_t cr1;
 //   uint32_t unused[2];
    uint32_t brr;
    
   // uint32_t unused[3];
    
    struct {
        unsigned int : 6;
        unsigned int tc:1;
        unsigned int txe:1;
        unsigned int: 24;
    }isr;
    uint32_t unused[2];
    uint32_t tdr;
    
}USART;

static volatile uint32_t * const usart2_isr= (uint32_t*)(USART2_BASE + 0x1c);
static volatile uint32_t * const usart2_tdr= (uint32_t*)(USART2_BASE + 0x28);

static volatile uint32_t * const usart2_cr1= (uint32_t*)(USART2_BASE + 0x00);

static volatile USART * const usart2 = (USART *)USART2_BASE;

void usart_putc(uint8_t c)
{
    while (!usart2-> isr.txe);
    usart2->tdr = c;
    while(!usart2->isr.tc);
}
void usart_puts(const char *str)
{
    char c;
    while ((c = *str++)){
    usart_putc(c);
    }
   
}
void usart_putx(uint32_t val)
{
    for(int i=1; i<=8; i++){
    uint8_t c = (val >> (32-i*4))& 0xF; // 15 = F 0x
    c = ((c <10) ? c + '0' : ( c+ 'A' -10));
    usart_putc(c);
    }
}


void usart_enable(void)
{

  usart2->cr1 = 0x00; //Reset USART2 
  usart2->brr = 0x00; //Reset USART2 Baud rate 
  set_bits(&usart2->brr, 417, 0); //Baudrate 4MHz / 9600 
  set_bits(&usart2->cr1, 1, 3); //TE enable
  set_bits(&usart2->cr1, 0b0, 15); //Oversampling by 16
  //usart2->cr1 |= (1 << 2); //RE enable
  set_bits(&usart2->cr1, 1, 0); //UE enable

}


