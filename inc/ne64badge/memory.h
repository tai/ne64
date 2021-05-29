#ifndef MEMORY_H
#define MEMORY_H

/**********************************************************************
 * memory map
 **********************************************************************/
#define REG_BASE 0x0000 /*  1KB - on reset, base=0x0000 */
#define RAM_BASE 0x2000 /*  8KB - on reset, base=0x0000 (REG overlayed) */
#define ROM_BASE 0x4000 /* 48KB - mapped from on-chip 64KB */

/* ROM area internals - special regions */
#define VEC_BASE 0xff00 /* 256B - included in ROM area */
#define BDM_BASE 0xff00 /* 256B - included in ROM area */

/* ROM area internals - Flash memory pages (16KB * 3) and protected areas */
#define ROM0_BASE         0x4000 /* 16KB fixed*/
#define ROM0_PROTECT_SIZE 4096   /* write protect from start address */
#define ROM1_BASE         0x8000 /* 16KB paged */
#define ROM2_BASE         0xc000 /* 16KB fixed*/
#define ROM2_PROTECT_SIZE 4096   /* write protect from end address */

#endif
