CC=arm-none-eabi-gcc 

OBJCOPY=arm-none-eabi-objcopy
CFLAGS=$(MCPU) $(MODE) $(DEBUG)
LDFLAGS=-nostartfiles -Wl,-Ttext=$(TEXTSECTIONADRESS) $(DEBUG)
DEBUG=-g

BUILD_DIR=build
BOARD_DIR=/media/ismail/NODE_F042K6
MKDIR=mkdir -p

#mcu specific options
MCPU=-mcpu=cortex-m0
MODE=-mthumb
TEXTSECTIONADRESS=0x8000000

OPENOCD_CONFIG=nucelo-l4.cfg
OPENOCD_START=openocd -f $(OPENOCD_CONFIG)
GDB_CONFIG=gdb_init.cfg
GDB_CONFIG_DEFAULT=gdb_init.cfg.default

.PHONY: all
all: directories $(BUILD_DIR)/blinky.bin

.PHONY: directories
directories:
	$(MKDIR) $(BUILD_DIR)

.PHONY: upload

upload: all
	cp $(BUILD_DIR)/blinky.bin $(BOARD_DIR)/

.PHONY: openocd 
openocd: $(OPENOCD_CONFIG)
	$(OPENOCD_START)

.PHONY: gdb
gdb: $(BUILD_DIR)/blinky.elf $(GDB_CONFIG) 
	gdb-multiarch --command=$(GDB_CONFIG) $<

.PHONY: reset_gdb
reset_gdb:
	echo target remote localhost:3333 >> $(GDB_CONFIG_DEFAULT)
	echo monitor reset init >> $(GDB_CONFIG_DEFAULT)
	echo tui enable >> $(GDB_CONFIG_DEFAULT)
	echo layout regs >> $(GDB_CONFIG_DEFAULT)

.PHONY: clean 
clean:
	rm -rf build


$(BUILD_DIR)/therealblinky.o: blinky.S
	$(CC) $< $(CFLAGS) -c -o $@

$(BUILD_DIR)/therealblinky.elf: $(BUILD_DIR)/blinky.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

$(BUILD_DIR)/therealblinky.bin: $(BUILD_DIR)/blinky.elf
	$(OBJCOPY) -O binary -S $< $@


$(GDB_CONFIG):
	
	
