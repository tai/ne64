#ifndef IO_H
#define IO_H

/* Basic bitmask macros */
#define BF(n)    ((1 << (n)) - 1) /* n-bit bitmask at offset 0 */
#define BM(p, n) (BF(n) << (p))   /* n-bit bitmask at offset p */
#define BV(p)    (1 << (p))       /* 1-bit bitmask at offset p */

/* Register bitmask/bitvector definition.
 *
 * For any register (say: register FPHS of port FPROT), following macros
 * are available:
 *
 * - FPROT_FPHS         : bitmask that covers FPHS register range in FPROT.
 * - FPROT_FPHS_        : offset of FPHS register in FPROT.
 * - OV(val, FPROT_FPHS): bit-shifts val to set FPHS value in FPROT.
 * - IV(val, FPROT_FPHS): masks and bit-shifts val to obtain FPHS value.
 *
 * Usage:
 *   // logically same, and both generate same binary
 *   FPROT = OV(3, FPROT_FPHS)|...;
 *   FPROT = (3 << FPROT_FPHS_)|...;
 *
 *   // logically same, but latter generates less binary
 *   if (IV(FPROT, FPROT_FPHS) == 3) ...;
 *   if ((FPROT & FPROT_FPHS) == OV(3, FPROT_FPHS)) ...;
 */
#define OV(val, name) ((val)        << name##_)
#define IV(val, name) ((val) & name >> name##_)

#define reg_4(port, p, name, len) rbm(p, port##_##name, len)
#define reg_3(port, p, name)      rbv(p, port##_##name)
#define reg(...) CAT(reg_, COUNT(__VA_ARGS__))(__VA_ARGS__)

#define regs_17(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_16(DEC(n), port, __VA_ARGS__)
#define regs_16(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_15(DEC(n), port, __VA_ARGS__)
#define regs_15(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_14(DEC(n), port, __VA_ARGS__)
#define regs_14(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_13(DEC(n), port, __VA_ARGS__)
#define regs_13(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_12(DEC(n), port, __VA_ARGS__)
#define regs_12(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_11(DEC(n), port, __VA_ARGS__)
#define regs_11(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_10(DEC(n), port, __VA_ARGS__)
#define regs_10(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_9(DEC(n), port, __VA_ARGS__)
#define regs_9(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_8(DEC(n), port, __VA_ARGS__)
#define regs_8(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_7(DEC(n), port, __VA_ARGS__)
#define regs_7(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_6(DEC(n), port, __VA_ARGS__)
#define regs_6(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_5(DEC(n), port, __VA_ARGS__)
#define regs_5(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_4(DEC(n), port, __VA_ARGS__)
#define regs_4(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_3(DEC(n), port, __VA_ARGS__)
#define regs_3(n, port, a, ...)                                 \
    reg(port, n, EXPAND(a)); regs_2(DEC(n), port, __VA_ARGS__)
#define regs_2(n, port, a, ...)                 \
    reg(port, n, EXPAND(a))
#define regs_1(n, port, a, ...) /* ignore sentinel */
#define regs(n, port, ...) CAT(regs_, COUNT(__VA_ARGS__))(n, port, __VA_ARGS__)

#define regw(...) regs(15, __VA_ARGS__, dummy)
#define regb(...) regs( 7, __VA_ARGS__, dummy)

/* SFR (Special Function Register) definition */
#ifdef __ASSEMBLER__
#define rbm(p, name, n) __##name = BM(p, n); __##name##_ = p
#define rbv(p, name) rbm(p, name, 1)

#define sfrb(addr, name, ...)  __##name = addr; regb(name, ##__VA_ARGS__)
#define sfrw(addr, name, ...)  __##name = addr; regw(name, ##__VA_ARGS__)
#define sfrn(addr, name, size) __##name = addr

#define const_sfrb(...) sfrb(__VA_ARGS__)
#define const_sfrw(...) sfrw(__VA_ARGS__)
#define const_sfrn(...) sfrn(__VA_ARGS__)
#else
#define rbm(p, name, n) enum { name = BM(p, n) }; enum { name##_ = p }
#define rbv(p, name) rbm(p, name, 1)

#define sfrb_(addr, name, ...)                       \
    volatile unsigned char name asm("__" #name);  \
    regb(name, ##__VA_ARGS__)
#define sfrw_(addr, name, ...)                       \
    volatile unsigned short name asm("__" #name);  \
    regw(name, ##__VA_ARGS__)
#define sfrn_(addr, name, n) \
    volatile unsigned char name[n] asm("__" #name)

#define sfrb(...) extern sfrb_(__VA_ARGS__)
#define sfrw(...) extern sfrw_(__VA_ARGS__)
#define sfrn(...) extern sfrn_(__VA_ARGS__)

#define const_sfrb(...) extern const sfrb_(__VA_ARGS__)
#define const_sfrw(...) extern const sfrw_(__VA_ARGS__)
#define const_sfrn(...) extern const sfrn_(__VA_ARGS__)
#endif

#endif
