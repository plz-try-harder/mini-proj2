	.global _start

	.equ STACK_HIGH,	0x20010000

Vectors:
	.word STACK_HIGH
	.word _start + 1
