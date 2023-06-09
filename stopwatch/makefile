.PHONY: all

all: stoppuhr.bin
stoppuhr.bin: stoppuhr.elf
	arm-none-eabi-objcopy -O binary -S stoppuhr.elf stoppuhr.bin
	
stoppuhr.elf: head.o usart.o stoppuhr.o bithelper.o utils.o
	arm-none-eabi-gcc head.o bithelper.o utils.o usart.o stoppuhr.o -mcpu=cortex-m0 -mthumb -nostartfiles -Wl,-Ttext=0x8000000,-Tdata=0x20000000 -o stopwatch.elf

head.o: head.S
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
usart.o: usart.c usart.h
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
bithelper.o: bithelper.c bithelper.h
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
utils.o: utils.c 
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@
	
stoppuhr.o: stoppuhr.c usart.c usart.h stoppuhr.h bithelper.c bithelper.h utils.c 
	arm-none-eabi-gcc $< -mcpu=cortex-m0 -mthumb -c -o $@

.PHONY: clean
clean:
	rm -f stoppuhr.bin stoppuhr.elf stoppuhr.o usart.o head.o bithelper.o utils.o
	
.PHONY: upload
upload: stoppuhr.bin
	cp stoppuhr.bin /media/$(USER)/NODE_L432KC



	
