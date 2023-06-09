.global _start

.syntax unified

.equ STACK_HIGH,		0x20010000

/* Relevant addresses and values for the RCC register bank */
	.equ RCC_BASE,		0x40021000
	.equ RCC_AHB2ENR,	RCC_BASE + 0x4c
	.equ RCC_AHB2ENR_PB,	(1<<1)

  /* Relevant addresses and values of the GPIOB register bank */
	.equ GPIOB_BASE,	0x48000400
	.equ GPIOB_MODER,	GPIOB_BASE + 0x00
	.equ GPIO_MODER_PIN3O,	(1<<0)
	.equ GPIOB_ODR,	GPIOB_BASE + 0x14
	.equ GPIO_PIN3_HIGH,	(1<<0)
	.equ GPIO_PIN3_LOW,	(0<<0)
	.equ GPIO_PUPDR,	GPIOB_BASE + 0x0C
	.equ GPIO_PUBDR_B5,	(1<<11)
	.equ GPIOB_IDR,	GPIOB_BASE + 0x10
	.equ GPIOB_IDR_B5,	(1<<5)

	.equ DELAY_750,	0x124803
  	.equ DELAY_250,	0x61801
	.equ DELAY_DEBOUNCE,	0x00100
	.equ BLINK_LOOP_RV,	0x00006

Vectors:
	.word STACK_HIGH	/* initial sp value */
	.word _start +1 
_start:
	ldr     r0, =RCC_AHB2ENR	/* load AHB1 Register adress */
	ldr	r1, [r0]		/* load value of AHB1 Register in R1 */
	ldr	r2, =RCC_AHB2ENR_PB	/* load GPIOB enable to R2 */
	orrs	r1, r2			/* R1 = R1 or R2 */
	str	r1, [r0]		/* store R1 in AHB1 register adress */

/* Configure GPIO pin as output */
	ldr	r0, =GPIOB_MODER
	ldr	r1, =GPIO_MODER_PIN3O
	str	r1, [r0]
  
 /* Configure GPIO_B5 pin as Pulldown-Input */
 	ldr	r0, =GPIO_PUPDR
 	ldr	r1, =GPIO_PUBDR_B5
 	str	r1, [r0]	
 
 
 /* 52 - 84: Button Read, Debounce, STANDBY-Mode */
 
 .stop_mode0:				// - read Button
	ldr	r0, =GPIOB_IDR		
	ldr	r0, [r0]
	ldr	r1, =GPIOB_IDR_B5
	tst	r0, r1 		// Z==0 if pushed
	beq	.skip			// skip if Z==1
	ldr	r2, =DELAY_DEBOUNCE
.stop_mode1:				// - debounce wait
	subs	r2, r2, #1
	bne	.stop_mode1		
.stop_mode2:				// - read Button again
	ldr	r0, =GPIOB_IDR
	ldr	r0, [r0]
	tst	r0, r1			// Z==0 if pushed
	beq	.skip			// skip if Z==1
	
	ldr	r0, =GPIOB_ODR		// - turn LED off
	ldr	r1, =GPIO_PIN3_LOW
	str	r1, [r0]
	ldr	r1, =GPIOB_IDR_B5	
	
.stop_mode3:				// - while input, read input - catch multiple inputs
	ldr	r0, =GPIOB_IDR	
	ldr	r0, [r0]
	tst	r0, r1			// Z==0 if pushed
	bne	.stop_mode3		// b if Z==0
	

.standby:				// - STANDBY - while no input, read input 
	ldr	r0, =GPIOB_IDR		
	ldr	r0, [r0]
	tst	r0, r1			// Z==0 if pushed
	beq	.standby		// loop if Z==1
	
	
/* 86 - 102: Button Read, Debounce, leave STANDBY */ 

	ldr	r2, =DELAY_DEBOUNCE
.stop_mode5:				// - debounce wait
	subs	r2, r2, #1
	bne	.stop_mode5
.stop_mode6:				// - read button again
	ldr	r0, =GPIOB_IDR		
	ldr	r0, [r0]
	tst	r0, r1			// Z==0 if pushed
	beq	.standby		// b if Z==1
.stop_mode7:				// - while input, read input - catch multiple inputs
	ldr	r0, =GPIOB_IDR		
	ldr	r0, [r0]
	tst	r0, r1			// Z==0 if pushed
	bne	.stop_mode7		// loop if Z==0
	

/* 107 - end: Loop of SOSBLINKY-Mode, read Button while every wait */

.skip:	
	ldr	r0, =GPIOB_ODR		// load address of GPIOB output data register in r0
  	ldr     r1, =GPIO_PIN3_HIGH	// load bitmask of gpio pin3 in r1
	ldr	r3, =BLINK_LOOP_RV	// reset blink loop register
.blink_S0:
  	str     r1, [r0]		// store current r1 into GPIOB output data register

  /* Busy wait */
  	ldr     r2, =DELAY_250

.loop0:
	ldr	r4, =GPIOB_IDR		// read input
	ldr	r4, [r4]
	ldr	r5, =GPIOB_IDR_B5
	tst	r4, r5			// Z==0 if pushed
	bne	.stop_mode0		// b if Z==0
  	subs    r2, r2, #1		// count down wait-loop
  	bne     .loop0
  	
  	eors    r1, #GPIO_PIN3_HIGH	// toggle bit corresponding to bit 3
	subs	r3, r3, #1 
	bne	.blink_S0		// loops long blinks three times
	ldr	r3, =BLINK_LOOP_RV	// reset blink loop register 

.blink_L:
  	str     r1, [r0]		// store current r1 into GPIOB output data register
  	ldr	r2, =GPIO_PIN3_HIGH	
  	tst	r1, r2			//see if LED is on: Z==0 if LED on
  	bne	.LED_ON		//branch if LED is on
  	ldr	r2, =DELAY_250		//short wait if LED off
  	b	.loop1
   
.LED_ON:				//long wait if LED on
  	ldr     r2, =DELAY_750

.loop1:
	ldr	r4, =GPIOB_IDR		// read input
	ldr	r4, [r4]
	tst	r4, r5
	bne	.stop_mode0
  	subs    r2, r2, #1		// count down wait-loop
  	bne     .loop1

  
  	eors    r1, #GPIO_PIN3_HIGH	// toggle bit corresponding to bit 3
 
	subs	r3, r3, #1 
	bne	.blink_L		// loops short blinks three times 
	ldr	r3, =BLINK_LOOP_RV	// reset blink loop register 
	
.blink_S1:
  	str     r1, [r0]		// store current r1 into GPIOB output data register
  	ldr     r2, =DELAY_250		// load wait-time

.loop_2:
	ldr	r4, =GPIOB_IDR		
	ldr	r4, [r4]
	tst	r4, r5
	bne	.stop_mode0
  	subs    r2, r2, #1
  	bne     .loop_2

  	eors    r1, #GPIO_PIN3_HIGH	// toggle bit corresponding to bit 3
 
	subs	r3, r3, #1 
	bne	.blink_S1		// loops long blinks three times 
	ldr	r3, =BLINK_LOOP_RV	// reset blink loop register 
	
/* Busy wait */
  	ldr     r2, =DELAY_750

.loop9:
	ldr	r4, =GPIOB_IDR		// read input
	ldr	r4, [r4]
	tst	r4, r5
	bne	.stop_mode0
  	subs    r2, r2, #1
  	bne     .loop9

  	b       .blink_S0		// start from top - repeat 

