# note for compilation: can call a specific function defined here by using
# [make func_name] --> e.g., make clean
AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
MACH=cortex-m4
AFLAGS=-c -mcpu=$(MACH) -mthumb -Wall -o0
CFLAGS=-c -mcpu=$(MACH) -mthumb --std=gnu11 -Wall -Wextra -Wpedantic -o0 -g3
LDFLAGS=-nostdlib -T stm32_ls.ld -Wl,-Map=final.map #-Wl specifies a linker input

all: main.o stm32_startup.o final.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o:startup_stm32f446xx.s
	$(AS) $(AFLAGS) -o $@ $^

final.elf: main.o stm32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf *.map

load:
	openocd -f board/st_nucleo_f4.cfg

client:
	arm-none-eabi-gdb

flash:
	# USE THIS ONE FOR OPENOCD 0.12.0-1!!!
	# openocd -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32f4x.cfg -c "program final.elf verify reset exit"

	# USE THIS ONE FOR OPENOCD 0.12.0-6!!!
	openocd -f interface/stlink.cfg -c "transport select dapdirect_swd" -f target/stm32f4x.cfg -c "program final.elf verify reset exit"

# -Wall: show all warnings
#  clean: function description deletes all .o and .elf files
#  -c: do not link the files
#  -o: create object files
#

