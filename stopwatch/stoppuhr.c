#include "usart.h"
#include "bithelper.h"
#include "stoppuhr.h"

static volatile GPIO_TypeDef * const gpioA = GPIOA;
static volatile GPIO_TypeDef * const gpioB = GPIOB;
static volatile RCC_TypeDef * const  rcc = RCC;
static volatile STK_TypeDef * const stk = STK;
static volatile SYSCFG_TypeDef * const syscfg = SYSCFG;
static volatile EXTI_TypeDef * const exti = EXTI;
static volatile uint32_t * const nvic_iser = (uint32_t *)(NVIC_ISER_BASE);

void usart_init(void);
void led_init(void);
void systick_init(void);
void led_set(int value);
void led_toggle(void);
int systick(void);
void exti_init(void);
void exti1(void);
void disable_irq(void);
void enable_irq(void);

uint32_t volatile time;
uint32_t stoppuhractive;



 

int _start(void) {
	usart_init();
	led_init();
	systick_init();
	exti_init();
	if(time == 0 && stoppuhractive == 0){
		while(1) 
		{
	  		usart_puts("Test\n Stoppuhr ist an\n");//   Stoppuhr Status Ausgabe
		
			usart_putx(time);
			
			__asm__ volatile ("WFI" : : : "memory");
			
				usart_putc('\n');
		}
		

	}
	else{
		usart_puts("Test\n Fehler\n");
	}
}

/*
* wenn stoppuhrActive der LED  nicht umgeschaltet : hält LED an. 
* sonst wird jeder halbe Sekunde gezählt, die seit dem Einschalten der Stoppuhr vergangen ist.
*/ 
int systick(void) {
	if(!stoppuhractive)	led_set(1);
	else{
	
		time++;
		led_toggle();
	}
	
	return 0;
}


int risingEdge = 0;
int fallingEdge = 0;

/**Stoppuhr wird ein/aus geschaltet, nachdem eine fallende als auch eine steigende Flanke des 
* Tastendrucks erkannt wurde:
* wenn die Stoppuhr eingeschaltet ist, werden die Zähler STK_VAL auf den Neuladewert und Zeit(halbe Sekunden) auf 0 zurÃ¼ckgesetzt
* wenn die Stoppuhr ausgeschaltet ist, die Zeit ist aktiv per USART2 

*/

void exti1(void) {
	//abfrage, ob Falling Edge erkannt wurde 
	if( !(gpioB->idr >> 1) & 1 ) {
		fallingEdge = 1;
	}
	//Abfrage, ob steigende Flanke nach fallender Flanke erkannt wird
	if( fallingEdge & (gpioB->idr >> 1) & 1 ) {
		risingEdge = 1;
	}
	//set_bits(nvic_ispr, 0b1, 7); //Set Pending State for EXTI1 Interrupt
	//AN1 & AN2
	if( risingEdge & fallingEdge ) {
		stoppuhractive = ~stoppuhractive;	//Schaltet Stoppuhr um
		if (!stoppuhractive) {
			risingEdge = 0;
			fallingEdge = 0;
			usart_puts( cvr2string(time, stk->val) );
		} else {
			time = 0; 
			stk->val = 2000000-1; //Resets STK_VAL
		}
	}
	
	set_bits(&exti->pr1, 0b1, 1); //Ends EXTI1 Interrupt




}



/*
* initialisiert den SYs Tick Timer
* werden SysTick Steuer- und Statusregister (STK_CTRL) zurückgestzt
* Die SysTick-Zähler und SysTick-Ausnahmeanforderung aktiviert
* Wird ein Prozessortakt als Taktquelle ausgewählt
* Und wird den SysTick-Reload-wert im Reload-Wert-Register(STK_LOAD) gesetzt
*fCK = 4MHz, T = 0.5s
*N = fCK * T = 2000000
* RELOAD = N-1 = 2000000-1
*/
void systick_init(void) {
	stk->ctrl = 0x0; //RESET
	set_bits(&stk->ctrl, 0b111, 0); //Enable SysTick Interrupt
	set_bits(&stk->load, 2000000-1, 0); //Trigger SysTick Interrupt every 0.5s
}




/* aktiviere USART2 TX für Pin A2
* Aktiviere USART2 Clock
* Aktiviere GPIO Clock
* Pin A2 wird auf Alternativfunktionsmodus gesetzt
* USART2 wird für Pin A2 gewählt
*Aktiviere USART2

*/
void usart_init(void) {

	set_bits(&rcc->apb1enr1,0b1, 17); //Enable USART2EN Clock (RM 221/1600)
	set_bits(&rcc->ahb2enr,0b1, 0); //GPIOA Clock
	
	set_bits(&gpioA->moder, 0b10, 4); 	//Alternative Function Mode Pin A2 (RM 267/1600)
	set_bits(&gpioA->afrl, 0b111, 8); 	//Alternative Function 7 USART2 (DS 56/156)
	usart_enable();
}

/*
* @brief Aktiviere GPIO B0 zu control LED
* GPIO B Clock wird gesetzt
* Pin B0 wird zu Output Mode gesetzt
*/
void led_init(void) {
	set_bits(&rcc->ahb2enr,0b1,1); //GPIOB Clock
	set_bits(&gpioB->moder, 0b0, 1); //GPIOB General purpose output mode
  set_bits(&gpioB->moder, 0b1, 0); //GPIOB General purpose output mode
}




void exti_init(void) {
	set_bits(&gpioB->moder, 0b0, 2); //Pin B1 Input Mode
	set_bits(&gpioB->moder, 0b0, 3); //Pin B1 Input Mode
	set_bits(&gpioB->pupdr, 0b1, 2); //Pin B1 Internal Pull-up
	set_bits(&gpioB->pupdr, 0b0, 3); //Pin B1 Internal Pull-up
	
	set_bits(&rcc->apb2enr, 0b1, 0); //SYSCFG Enable (RM223/1600)
	set_bits(&syscfg->exticr1, 0b0, 6); //EXTI Config Pin B1
	set_bits(&syscfg->exticr1, 0b0, 5); //EXTI Config Pin B1
	set_bits(&syscfg->exticr1, 0b1, 4); //EXTI Config Pin B1
	
	set_bits(&exti->imr1, 0b1, 1); //Disable EXTI Line 1 Interrupt mask
	set_bits(&exti->rtsr1, 0b1, 1); //Enable Rising edge trigger
	set_bits(&exti->ftsr1, 0b1, 1); //Enable Falling edge trigger
	
	set_bits(nvic_iser, 0b1, 7); //Enable Interrupt for EXTI line 1
		
}

// LED Anschalten wenn wert nicht 0 ist.
void led_set(int value) {
	if (0 == value) set_bits(&gpioB->odr, 0b1, 0);
	else set_bits(&gpioB->odr, 0b0, 0);
	
}

/*
* LED umschalten
* schalte die LED aus, wenn sie gerade an ist
* schalte die LED an, wenn sie gerade aus ist

*/

void led_toggle(void) {
	set_bits(&gpioB->odr, ~((gpioB->odr >> 0) & 1), 0);
}

/**
 *  deaktiviere Interrupt-Anfragen
 */
void disable_irq(void)
{
	__asm__ volatile ("cpsid i" : : : "memory"); //Disable Interrupts
}




/** aktiviere Interrupt-Anfragen */
void enable_irq(void)
{
	__asm__ volatile ("cpsie i" : : : "memory"); //Enable Interrupts
}





