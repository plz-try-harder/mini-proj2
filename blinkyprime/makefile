.PHONY: all
all: blinkyprime.bin

blinkyprime.bin: blinkyprime.elf
	arm-none-eabi-objcopy -O binary -S blinkyprime.elf blinkyprime.bin
	
blinkyprime.elf: head.o usart.o gpio.o rcc.o blinkyprime.o 
	arm-none-eabi-gcc head.o usart.o gpio.o rcc.o blinkyprime.o -mcpu=cortex-m0 -mthumb -nostartfiles -Wl,-Ttext=0x8000000 -o blinkyprime.elf

head.o: head.S
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
usart.o: usart.c usart.h 
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
gpio.o: gpio.c gpio.h 
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
rcc.o: rcc.c rcc.h 
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
blinkyprime.o: blinkyprime.c usart.c usart.h gpio.c gpio.h rcc.c rcc.h 
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@

.PHONY: clean
clean:
	rm -f blinkyprime.bin blinkyprime.elf blinkyprime.o usart.o head.o gpio. rcc.o gpio.o
.PHONY: upload
upload: blinkyprime.bin
	cp blinkyprime.bin /media/$(USER)/NODE_L432KC

	
