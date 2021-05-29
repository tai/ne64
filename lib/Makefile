# trick to resolve Makefile-relative path
SELF := $(abspath $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
HERE := $(dir $(SELF))

TARGET = crt0.o

XINC = $(HERE)/../inc
XLIB = $(HERE)

# for generic gcc/ld arch lookup
MCU = 68hcs12

# for linker script lookup (used to switch periph.x, etc)
DEV = mc9s12ne64

CDEFS   = -I$(XINC) -D$(DEV)
LIBS    = -L$(XLIB) -L$(XLIB)/$(DEV) -Wl,-T$(MCU).x

# see also: "m9s12x-elf-(gcc|as|ld) --target-help"
CFLAGS  = $(EXTRA_CLAGS) \
	-g -Os -std=gnu99 -Wall -Wstrict-prototypes -Wshadow $(CDEFS) \
	-m$(MCU) -mshort -mrelax -minmax -mauto-incdec \
	-fomit-frame-pointer -ffunction-sections -fdata-sections
LDFLAGS = $(EXTRA_LDFLAGS) \
	-m$(MCU) -mshort -mrelax -nostartfiles \
	-Wl,--warn-common -Wl,--print-gc-sections -Wl,--gc-sections \
	-Wl,--bank-window,REGION_BANK -Wl,--no-trampoline

CROSS = m9s12x-elf-
CC      = $(CROSS)gcc
LD      = $(CROSS)gcc
SIZE    = $(CROSS)size
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

.SUFFIXES: .S .c .o .elf .s19 .dump
.PRECIOUS: $(ELFS)
.SECONDEXPANSION:

.S.o:
	$(CC) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

.elf.s19:
	$(OBJCOPY) -O srec $< $@

.elf.dump:
	$(OBJDUMP) -s --start-address=0x4000 $< > $@
	$(OBJDUMP) -dS $< >> $@

all: $(TARGET)
	$(MAKE) -C lds $@

clean:
	$(MAKE) -C lds $@
	$(RM) *.o *.elf *.s19 *.map *.dump *~
