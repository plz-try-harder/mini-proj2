.global _start

.syntax unified

.equ STACK_HIGH, 	0x20010000

/* Relevant addresses and values for the RCC register bank */

.equ RCC_BASE, 0x40021000
.equ RCC_AHB1ENR,	RCC_BASE + 0x4c
.equ RCC_AHB1ENR_PB,	(1<<1)

/* Relevant addresses and values of the GPIOB register bank */

.equ GPIOB_BASE, 	0x48000400
.equ GPIOB_MODER,	GPIOB_BASE + 0x00
.equ GPIO_MODER_PIN3O,	(1<<6)
.equ GPIOB_ODR,	GPIOB_BASE + 0x14
.equ GPIO_PIN3_HIGH, 	(1<<3)

.equ DELAY,  		0x186004  //1000 ms
.equ DELAY250,		0x61801   //250  ms
.equ DELAY750,		0x124803  //750  ms
.equ DELAY1750,	0x2AA807  //1750 ms

Vectors:
	.word STACK_HIGH	/* initial sp value */
	
	.word _start + 1
	
_start:
/* Get contents of AHB2 bus clock enable register */
ldr	r0, =RCC_AHB1ENR
ldr	r1, [r0]

/* Set bit to enable clock for GPIO port B */
ldr	r2, =RCC_AHB1ENR_PB
orrs	r1, r2
str	r1, [r0]	

/* Configure GPIO pin as output */
ldr	r0, =GPIOB_MODER
ldr	r1, =GPIO_MODER_PIN3O
str	r1, [r0]

/* Load address of GPIOB output data register in r0 */
ldr	r0, =GPIOB_ODR

/* Load bitmask of gpio pin3 in r1 */
ldr	r1, =GPIO_PIN3_HIGH



.blink:

/***Blink_Mode_1_start***/
ldr	r3, =0x6

.blink1:


str	r1, [r0]
ldr	r2, =DELAY250

.loop15:                  
subs	r2, r2, #1 /* r2 = r2-1 das dauert 250ms  */ 
bne	.loop15  	
eors	r1, #GPIO_PIN3_HIGH

subs	r3, r3, #1
bne	.blink1
/***Blink_Mode_1_Finish***/




/***Blink_Mode_2_start***/
ldr	r3, =0x3
.blink2:

str	r1, [r0] /*Turn GPIO Pin_A5 on*/
ldr	r2, =DELAY250  /*load the value of 250ms in r2*/


.loop12:                  
subs	r2, r2, #1 /*r2 = r2-1 das dauert 250ms  */ 
bne	.loop12  	/* Die Schleifekontrolle beendet den Loop, wenn r2 == 0 ist*/
eors	r1, #GPIO_PIN3_HIGH
subs	r3, r3, #1     
bne	.blink2	


ldr	r3, =0x6
/***Blinking_Mode_2_Finish***/



/***Blinking_Mode_3_start***/

.blink3:

str	r1, [r0]
ldr	r2, =DELAY250

.loop26:                  
subs	r2, r2, #1 /*r2 = r2-1 das dauert 250ms  */ 
bne	.loop26  	
eors	r1, #GPIO_PIN3_HIGH

subs	r3, r3, #1
bne	.blink3
/***Blinking_Mode_3_Finish***/



/* Delay */
ldr	r2, =DELAY1750 /* load the value of DELAY1750 into r2 */

.loop45:
subs	r2, r2, #1
bne	.loop45


/* repeat the whole process */

b	.blink
