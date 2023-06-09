.PHONY: all
all: sosblinky2.bin
sosblinky2.bin: sosblinky2.elf
	arm-none-eabi-objcopy -g -O binary -S sosblinky2.elf sosblinky2.bin
sosblinky2.elf: sosblinky2.o
	arm-none-eabi-gcc -g sosblinky2.o -nostartfiles -Wl,-Ttext=0x8000000 -o sosblinky2.elf
sosblinky2.o: sosblinky2.S
	arm-none-eabi-gcc -g sosblinky2.S -mcpu=cortex-m4 -mthumb -c -o sosblinky2.o
	
.PHONY: clean
clean:
	rm -f sosblinky2.o sosblinky2.elf sosblinky2.bin

.PHONY: upload
upload: sosblinky2.bin
	cp sosblinky2.bin /media/$(USER)/NODE_L432KC
.PHONY: op 
op: 	
	openocd -f nucleo-l4.cfg
	
.PHONY: gdb
gdb: 	
	gdb-multiarch blinky.elf

	
