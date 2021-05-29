/**********************************************************************
 * Linker script for Future Electronics NE64 PoE Badge board.
 *
 * This board is based on Freescale MC9S12NE64 (64KB Flash, 8KB RAM),
 * and comes with on-board Ethernet, XBee(S1P)-over-UART, and standard
 * RS232 UART.
 *
 * NOTES:
 * - Check result with "objdump -h" so no unhandled section exists.
 * - All multi-byte values are in target endian - i.e, big endian.
 **********************************************************************/

#include "ne64badge/config.h"
#include "macro.h"

OUTPUT_FORMAT("elf32-m68hc12")
OUTPUT_ARCH(m68hc12)

INCLUDE memory.lds
INCLUDE periph.lds

ENTRY(_start)

/* macro to set common prefix (.hc12) to all non-standard sections */
#define XSECT(name) \
    *(.hc12.name .hc12.name.*); KEEP(*(.hc12.keep.name .hc12.keep.name.*))

/**********************************************************************
 * Banked memory support.
 * This must be defined first to use filename-based bank relocation.
 *
 * NOTE:
 * - By giving "far" attribute to a function, HC1x gcc will automatically
 *   generate CALL/RTC opcode with appropriate PPAGE arg.
 * - No such support is provided for data access, but it can be accessed
 *   somewhat transparently if both text/data belongs to the same bank.
 *   Else, it is up to developer to set correct PPAGE before access.
 **********************************************************************/
#define BANK_NAMED(name) SECTIONS { .hc12.##name : { \
        XSECT(name); \
        /* filename-based relocation. ex: bank3c*.o -> bank3c */ \
        name##*.o(.text .text.* .rodata .rodata.*) \
    } >CG_##name AT >FP_##name }
#define BANK(nn) BANK_NAMED(bank##nn)

/* banked pages */
MAP_S(BANK, 3f, 3e, 3d, 3c, 3b, 3a, 39, 38)
MAP_S(BANK, 37, 36, 35, 34, 33, 32, 31, 30)
MAP_S(BANK, 2f, 2e, 2d, 2c, 2b, 2a, 29, 28)
MAP_S(BANK, 27, 26, 25, 24, 23, 22, 21, 20)
MAP_S(BANK, 1f, 1e, 1d, 1c, 1b, 1a, 19, 18)
MAP_S(BANK, 17, 16, 15, 14, 13, 12, 11, 10)
MAP_S(BANK, 0f, 0e, 0d, 0c, 0b, 0a, 09, 08)
MAP_S(BANK, 07, 06, 05, 04, 03, 02, 01, 00)

#define BSEC(nn) .hc12.bank##nn
NOCROSSREFS(
MAP_S(BSEC,         3d, 3c, 3b, 3a, 39, 38)
MAP_S(BSEC, 37, 36, 35, 34, 33, 32, 31, 30)
MAP_S(BSEC, 2f, 2e, 2d, 2c, 2b, 2a, 29, 28)
MAP_S(BSEC, 27, 26, 25, 24, 23, 22, 21, 20)
MAP_S(BSEC, 1f, 1e, 1d, 1c, 1b, 1a, 19, 18)
MAP_S(BSEC, 17, 16, 15, 14, 13, 12, 11, 10)
MAP_S(BSEC, 0f, 0e, 0d, 0c, 0b, 0a, 09, 08)
MAP_S(BSEC, 07, 06, 05, 04, 03, 02, 01, 00)
)

/**********************************************************************
 * Basic sections
 **********************************************************************/

/* use stack in top-to-bottom direction */
__stack_start = ORIGIN(REGION_DATA) + LENGTH(REGION_DATA);

SECTIONS {
    /* NOTE: It seems HC12 gcc does not use page0 section */
    .page0 : { *(.page0) } >REGION_PAGE0

    .hc12.boot : {
        crt0.o(.text .text.* .rodata .rodata.*)
        XSECT(boot);
        KEEP(*(.tramp .tramp.*)) /* Seems only needed for HC11 farcall */
    } >REGION_BOOT

    /* protected high sectors */
    __end = ORIGIN(REGION_BOOT) + LENGTH(REGION_BOOT);
    .hc12.boot16k MAX(., __end - 16K) : { XSECT(boot16k); } >REGION_BOOT
    .hc12.boot8k  MAX(., __end -  8K) : { XSECT(boot8k);  } >REGION_BOOT
    .hc12.boot4k  MAX(., __end -  4K) : { XSECT(boot4k);  } >REGION_BOOT
    .hc12.boot2k  MAX(., __end -  2K) : { XSECT(boot2k);  } >REGION_BOOT

    .text : {
        /* protected low sectors (assignments are for range check) */
        XSECT(text0k); . = . <= 512 ? . : 0;
        XSECT(text1k); . = . <= 1K  ? . : 0;
        XSECT(text2k); . = . <= 2K  ? . : 0;
        XSECT(text4k); . = . <= 4K  ? . : 0;
        XSECT(text);

        /* usual binary comes here */
        *(.text .text.* .gnu.linkonce.t.*)
    } >REGION_TEXT AT >FP_TEXT

    .rodata : {
        . = ALIGN(2);
        /* KEEP is to protect from "--gc-sections" */
        __init_start = ABSOLUTE(.);
        KEEP(*(SORT(.init)))
        KEEP(*(SORT(.init.*)))
        __init_end = ABSOLUTE(.);

        XSECT(rodata);

        /* usual readonly data comes here */
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    } >REGION_TEXT AT >FP_TEXT

#ifdef CONFIG_BUFMAP
    /* Ethernet buffer (RX-A + RX-B + TX), starting from RAM base */
    .hc12.bufmap : {
        __RXBUF_A = ABSOLUTE(.); . = . + RXTX_BUFSIZE;
        __RXBUF_B = ABSOLUTE(.); . = . + RXTX_BUFSIZE;
        __TXBUF   = ABSOLUTE(.); . = . + RXTX_BUFSIZE;
    } >REGION_DATA
#endif

    /* RAM-allocated data with non-zero initial value */
    .data : {
        __data_start = ABSOLUTE(.);
        *(.data)
        *(SORT_BY_ALIGNMENT(.data.*))
        *(.gnu.linkonce.d.*)
        __data_end = ABSOLUTE(.);
    } >REGION_DATA AT >FP_TEXT =0xFF
    __data_size = SIZEOF(.data);
    __data_start_lma = ORIGIN(REGION_TEXT) + LOADADDR(.data) - ORIGIN(FP_TEXT);

    /* RAM-allocated data with no initial value (= 0) */
    .bss : {
        __bss_start = ABSOLUTE(.);

        __softregs_start = ABSOLUTE(.);
        *(.softregs) /* GCC-HC1x soft registers */
        __softregs_end = ABSOLUTE(.);

        *(.bss)
        *(SORT_BY_ALIGNMENT(.bss.*))
        *(.gnu.linkonce.b.*)
        *(COMMON)
        __bss_end = ABSOLUTE(.);
    } >REGION_DATA
    __bss_size = SIZEOF(.bss);

    /* config bits support */
    .hc12.config 0xFF00 : {
        __base = ABSOLUTE(.);

        /* 8-byte backdoor key */
        . = 0xFF00 - __base; FILL(0xFF); XSECT(backdoor);
        . = 0xFF07 - __base + 1; /* overrun detection */

        /* flash memory security and protection */
        . = 0xFF0D - __base; FILL(0xFF); XSECT(fprot);
        . = 0xFF0E - __base; FILL(0xFF); XSECT(fctl);
        . = 0xFF0F - __base; FILL(0xFE); XSECT(fsec);
        . = 0xFF0F - __base + 1; /* overrun detection */

        /* placeholder to enable filling */
        BYTE(0xFF);
    } >REGION_VECTOR

#define VECF(v, f) \
    __hc12_##v = ABSOLUTE(.); SHORT(DEFINED(__isr_##v) ? __isr_##v : f)
#define VECD(v) VECF(v, __isr_default)

    /* interrupt vectors - use ISR macro to override */
    .hc12.vectors 0xFFA0 : {
        __base = ABSOLUTE(.);

        . = 0xFFA0 - __base;
        VECD(vemacec)
        VECD(vemaclc)
        VECD(vemacbrxerr)
        VECD(vemacrxbbo)
        VECD(vemacrxbao)
        VECD(vemacrxerr)
        VECD(vemacmii)
        VECD(vemacrxfc)
        VECD(vemactxc)
        VECD(vemacrxbbc)
        VECD(vemacrxbac)
        VECD(vephy)
        VECD(vflash)

        . = 0xFFC0 - __base;
        VECD(viic)

        . = 0xFFC4 - __base;
        VECD(vcrgsrm)
        VECD(vcrgplllck)

        . = 0xFFCA - __base;
        VECD(vportg)
        VECD(vporth)
        VECD(vportj)
        
        . = 0xFFD2 - __base;
        VECD(vatd)
        VECD(vsci1)
        VECD(vsci0)
        VECD(vspi)
        VECD(vtimpaie)
        VECD(vtimpaovf)
        VECD(vtimovf)
        VECD(vtimch7)
        VECD(vtimch6)
        VECD(vtimch5)
        VECD(vtimch4)

        . = 0xFFF0 - __base;
        VECD(vrti)
        VECD(virq)
        VECD(vxirq)
        VECD(vswi)
        VECD(vtrap)
        VECD(vcop)
        VECD(vclkmon)
        VECF(vreset, _start)
    } >REGION_VECTOR =0xFFFF
}

/**********************************************************************
 * Auxiliary sections (mostly for debugging)
 **********************************************************************/
SECTIONS {
    /* Stabs for profiling information */
    .profiler 0 : { *(.profiler) }

    /* Stabs for debugging sections */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }

    /* DWARF 1 */
    .debug 0 : { *(.debug) }
    .line  0 : { *(.line) }

    /* GNU DWARF 1 extensions */
    .debug_srcinfo 0 : { *(.debug_srcinfo) }
    .debug_sfnames 0 : { *(.debug_sfnames) }

    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }

    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info) *(.gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
}

/*
 * Local Variables:
 * mode: ld-script
 * coding: utf-8-unix
 * End:
 */
