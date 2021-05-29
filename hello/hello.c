// LED sample

#include <stdint.h>
#include <string.h>

#include "ne64badge.h"

void
usleep(int us) {
    while (us--) asm("nop");
}

void AT(bank3d, far)
msleep(int ms) {
    while (ms--) usleep(1000);
}

void
xputchar(char c) {
    while (! (SCI0SR1 & SCISR1_TDRE)); // wait for data register to be empty
    SCI0DRL = c;
}

void AT(bank3c, far)
xputs(const char *s) {
    while (*s) {
        xputchar(*s++);
    }
}

static int count = 3;

int
main(void) {
    int i;

    for (i = 0; i < count; i++) {
        PTJ = 0x00;
        msleep(100);
        PTJ = 0xFF;
        msleep(100);
    }

    //memcpy((void *)MCHASH, buf, 8);

    for (;;) {
        xputs("hello, world\r\n");
        PTJ = 0x00;
        msleep(1000);
        PTJ = 0xFF;
        msleep(1000);
    }
}
