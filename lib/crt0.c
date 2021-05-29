//
// Custom startup for NE64 BADGE board
//

#include <string.h>
#include "ne64badge.h"

typedef void (*hook_t)(void);

// default "catch-all" interrupt handler
ISR(default,weak) {}

// call init hooks (initializers/constructors)
static void
init(void) {
    extern hook_t __init_start, __init_end;
    for (hook_t *fp = &__init_start; fp < &__init_end; fp++) {
        (*fp)();
    }
}

// Entry point
void __attribute__((noreturn))
_start(void) {
    /**********************************************************************
     * memory map configuration
     *
     * see also:
     * - http://forums.freescale.com/t5/16-Bit-Microcontrollers/
     *   Regarding-MC9S12NE64-INITRM-REGISTER/td-p/3520
     * - EB386.pdf
     **********************************************************************/
    // init SP
    extern char __stack_start;
    asm("lds %0" :: "i"(&__stack_start));

    // relocate RAM region
    //
    // NOTE:
    // - This must be done before any stack op (ex. function call)
    // - INITRM[3..7]: upper 5-bits of RAM base address
    INITRM = ((RAM_BASE >> 11) << 3);

    // initialize RAM region (for zero-valued bss)
    extern char __bss_start, __bss_size;
    memset((void *)&__bss_start, 0, (int)&__bss_size);

    // initialize RAM region (for data)
    extern char __data_start, __data_start_lma, __data_size;
    memcpy((void *)&__data_start,
           (void *)&__data_start_lma, (int)&__data_size);

    // run application
    extern void main(void);
    init(); main(); for (;;);
}
