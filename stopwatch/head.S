  .global _start
  .global systick
  .global exti1
  
  
  
  .syntax unified
  
  
  
  .equ STACK_HIGH, 					0x20010000 
  .equ SRAM_BASE,           0x20000000
  .equ SRAM_END,            0x2000FFFF
  .equ FLASH_BASE,          0x08000000  
  
  
  
Vectors:
  .word STACK_HIGH /* initial value of the sp */
  .word _start + 1
  .org 0x0000003C /* System tick timer  */
  .word systick
  .org 0x0000005C /* EXTI Line1 interrupt  */
  .word exti1

