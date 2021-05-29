#ifndef MC9S12_H
#define MC9S12_H

#include "macro.h"

#if defined(mc9s12ne64)
#include "mc9s12ne64.h"
#else
#error "Unknown or no device macro defined (ex: -Dmc9s12ne64)."
#endif

/**********************************************************************
 * Macros for HCS12-specific section assignment.
 **********************************************************************/

/*
 * Usage:
 *   void AT(bank3c,far) farfunc(void) { ... }
 *   char AT(bank3c) buf[] = { ... }
 */
#define AT(s, ...)                                                      \
    __attribute__((section(".hc12." #s "." __FILE__ ":" STR(__LINE__)), \
                   ##__VA_ARGS__))

/**********************************************************************
 * Macros for defining/registering pre-main hooks.
 *
 * Example:
 * INIT(my_init, INIT_DEV) {
 *     ...custom initialization comes here...
 * }
 **********************************************************************/

#define __add_hook(sec, level, fn)                                      \
    static void (*CAT(__##sec##_##level##_##fn##_L, __LINE__))(void)    \
        __attribute__((used,section("." #sec "." #level))) = fn;

#define INIT(fn, n)                                            \
    static void AT(boot) fn(void); __add_hook(init, n, fn);    \
    static void fn(void)

/* Initialization levels (orders) - even numbers are reserved */
#define INIT_EARLY 1
#define INIT_DEV   3
#define INIT_BOARD 5
#define INIT_APP   7

/**********************************************************************
 * Macros for defining interrupt handlers.
 *
 * Example:
 * ISR(vsci0) { // use vector name defined in datasheet table (1-7)
 *    ...handler code...
 * }
 **********************************************************************/

#define ISR(name, ...)                                                  \
    void AT(keep.boot,interrupt,used, ##__VA_ARGS__) __isr_##name(void)

#define ISR_NAKED(name, ...)                                            \
    void AT(keep.boot,noreturn,used, ##__VA_ARGS__) __isr_##name(void)

#define syscall(...) __isr_vswi(__VA_ARGS__)

#endif
