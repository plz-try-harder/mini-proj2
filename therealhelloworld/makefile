.PHONY: all

all: therealhelloworld.bin
therealhelloworld.bin: therealhelloworld.elf
	arm-none-eabi-objcopy -O binary -S therealhelloworld.elf therealhelloworld.bin

head.o: head.S
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@

usart.o: usart.c
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
gpio.o: gpio.c gpio.h
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
rcc.o: rcc.c rcc.h

	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@

therealhelloworld.o: therealhelloworld.c usart.c usart.h gpio.c gpio.h rcc.c rcc.h
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
therealhelloworld.elf: head.o usart.o gpio.o rcc.o therealhelloworld.o
	arm-none-eabi-gcc head.o usart.o gpio.o rcc.o therealhelloworld.o -mcpu=cortex-m0 -mthumb -nostartfiles -Wl,-Ttext=0x8000000 -o therealhelloworld.elf

.PHONY: clean
clean:
	rm -f therealhelloworld.bin therealhelloworld.elf therealhelloworld.o usart.o head.o gpio. rcc.o gpio.o
.PHONY: upload
upload: therealhelloworld.bin
	cp therealhelloworld.bin /media/$(USER)/NODE_L432KC
