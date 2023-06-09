.PHONY: all
all: sosblinky.bin
sosblinky.bin: sosblinky.elf
	arm-none-eabi-objcopy -g -O binary -S sosblinky.elf sosblinky.bin
sosblinky.elf: sosblinky.o
	arm-none-eabi-gcc -g sosblinky.o -nostartfiles -Wl,-Ttext=0x8000000 -o sosblinky.elf
sosblinky.o: sosblinky.S
	arm-none-eabi-gcc -g sosblinky.S -mcpu=cortex-m4 -mthumb -c -o sosblinky.o
	
.PHONY: clean
clean:
	rm -f sosblinky.o sosblinky.elf sosblinky.bin

.PHONY: upload
upload: sosblinky.bin
	cp sosblinky.bin /media/$(USER)/NODE_L432KC
.PHONY: op 
op: 	
	openocd -f nucleo-l4.cfg
	
	
.PHONY: gdb
gdb:	upload
	gdb-multiarch sosblinky2.elf -ex "target remote localhost:3333" -ex "monitor reset init" -ex "tui enable"
	
