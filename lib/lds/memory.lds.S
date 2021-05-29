#include "ne64badge/memory.h"
#include "macro.h"

/* Basic memory map */
MEMORY {
    /*
     * With HC11, it was possible to map ".softreg" section to RAM on PAGE0.
     * With HC12, it is not possible anymore.
     * So this region definition is left mostly for historic reason.
     *
     * SEE ALSO:
     * - http://tech.groups.yahoo.com/group/gnu-m68hc11/message/8524
     */
    REGION_PAGE0 (rwx) : ORIGIN = 0x0000, LENGTH = 256

    /* MCU-space memory map */
    REGION_DATA  (rwx) : ORIGIN = 0x2000, LENGTH = 8K
    REGION_TEXT   (rx) : ORIGIN = 0x4000, LENGTH = 16K
    REGION_BANK   (rx) : ORIGIN = 0x8000, LENGTH = 16K
    REGION_BOOT   (rx) : ORIGIN = 0xc000, LENGTH = 16K - 256
    REGION_VECTOR (rx) : ORIGIN = 0xff00, LENGTH = 256
}

/*
 * Additional memory map for banked region.
 *
 * With gcc, all calls to VMA address above $10000 (64KB) will
 * generate CALL/RTC opcode which loads appropriate memory bank
 * to $8000-$BFFF region prior to actual call. This is because
 * HCS12 uses banking to support up to 1MB (later: 4MB) memory
 * with 16bit addressing. Bank switching is done by writing a
 * bank (page) number to PPAGE register. For example,
 *
 *     farfunc(); // farfunc is placed on $100000 by linker script
 *
 * will generate
 *
 *     call $8000, $3C // PPAGE = $3C
 *
 * This means banked code/data located above $1xxxx region will
 * have their true VMA address (during execution) of $8xxx.
 *
 * Also, programming tool (BDM programmer, etc) has similar
 * convention so it can tell which banked region to program.
 * Current convention (CodeWarrior, USBDM, etc) is to generate
 * binary with LMA address of $<PPAGE>8xxx, and the tool will
 * set PPAGE before programming $8xxx region.
 *
 * | NOTE:
 * | It is unclear how this flash programming works with external
 * | memory configuration, but it's probably up to each developer
 * | to program external ROM/Flash separately.
 *
 * SEE ALSO:
 * - http://www.gnu-m68hc11.org/wiki/index.php/FAQ:Link
 *   #How_can_I_link_in_several_memory_banks.3F
 * - http://forums.freescale.com/t5/OSBDM-JM60-Open-Source-BDM-for/
 *   Can-USBDM-program-to-ROM-space/td-p/100419
 */

/* address conventions for code generation and flash programming */
#define CG_ADDR(nn) 0x##nn * 0x4000 + 0x10000
#define FP_ADDR(nn) 0x##nn##8000

/* macros for compact bank definition */
#define BANK_NAMED(nn, name) \
    MEMORY { CG_##name (rx) : ORIGIN = CG_ADDR(nn), LENGTH = 16K } \
    MEMORY { FP_##name (rx) : ORIGIN = FP_ADDR(nn), LENGTH = 16K }
#define BANK(nn) BANK_NAMED(nn, bank##nn)

/* always-mapped pages */
BANK_NAMED(3f, BOOT)
BANK_NAMED(3e, TEXT)

/* banked pages */
MAP_S(BANK, 3f, 3e, 3d, 3c, 3b, 3a, 39, 38)
MAP_S(BANK, 37, 36, 35, 34, 33, 32, 31, 30)
MAP_S(BANK, 2f, 2e, 2d, 2c, 2b, 2a, 29, 28)
MAP_S(BANK, 27, 26, 25, 24, 23, 22, 21, 20)
MAP_S(BANK, 1f, 1e, 1d, 1c, 1b, 1a, 19, 18)
MAP_S(BANK, 17, 16, 15, 14, 13, 12, 11, 10)
MAP_S(BANK, 0f, 0e, 0d, 0c, 0b, 0a, 09, 08)
MAP_S(BANK, 07, 06, 05, 04, 03, 02, 01, 00)

/*
 * Local Variables:
 * mode: ld-script
 * coding: utf-8-unix
 * End:
 */
