# trick to resolve Makefile-relative path
SELF := $(abspath $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
HERE := $(dir $(SELF))

XINC = $(HERE)/../../inc
XLIB = $(HERE)

DEV = mc9s12ne64

CFLAGS = -I$(XINC) -D$(DEV)

SRC = $(wildcard *.lds.S)
LDS = $(SRC:.S=)

CROSS = m9s12x-elf-
CC      = $(CROSS)gcc
LD      = $(CROSS)gcc
SIZE    = $(CROSS)size
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

.SUFFIXES:
.SUFFIXES: .lds .S

all: $(LDS)

$(LDS): %.lds: %.lds.S
	$(CC) $(CFLAGS) -C -P -E $< > $@

clean:
	$(RM) *.lds *~
