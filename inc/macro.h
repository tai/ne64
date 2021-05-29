#ifndef MACRO_H
#define MACRO_H

#define STR_(s) #s
#define STR(s) STR_(s)

#define COUNT_(_32,_31,_30,_29,_28,_27,_26,_25,                         \
               _24,_23,_22,_21,_20,_19,_18,_17,                         \
               _16,_15,_14,_13,_12,_11,_10,_09,                         \
               _08,_07,_06,_05,_04,_03,_02,_01, n, ...) n
#define COUNT(...)                                                      \
    COUNT_(__VA_ARGS__,                                                 \
           32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,             \
           16,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/*
 * Macros for nested argument.
 *
 * This can be used to pass around parameter in nested list form as
 * preprocessor treats args wrapped with parentheses as single argument.
 * It can be unnested at the time of processing with following macro:
 *
 *   #define FOO(a, b, c) BAR(xx, EXPAND(b))
 *   FOO(10, (20, 1), 30)  // -> BAR(xx, 20, 1)
 *   FOO(10, 20, 30)       // -> BAR(xx, 20)
 *
 * This is useful when handling complex data structures.
 */
#define EVAL(x) x
#define LIST(...) __VA_ARGS__
#define EXPAND_1(a) a
#define EXPAND_2(a) EVAL(LIST a)
#define EXPAND_3(a) EVAL(LIST a)
#define EXPAND_4(a) EVAL(LIST a)
#define EXPAND_5(a) EVAL(LIST a)
#define EXPAND_6(a) EVAL(LIST a)
#define EXPAND_7(a) EVAL(LIST a)
#define EXPAND_8(a) EVAL(LIST a)
#define EXPAND(a) CAT(EXPAND_, COUNT(EVAL(LIST a)))(a)

#define APPLY(fn, ...) fn(__VA_ARGS__)

#define CAT_(a,b)     a##b
#define CAT_1(a)      a
#define CAT_2(a, ...) APPLY(CAT_, a, CAT_1(__VA_ARGS__))
#define CAT_3(a, ...) APPLY(CAT_, a, CAT_2(__VA_ARGS__))
#define CAT_4(a, ...) APPLY(CAT_, a, CAT_3(__VA_ARGS__))
#define CAT_5(a, ...) APPLY(CAT_, a, CAT_4(__VA_ARGS__))
#define CAT_6(a, ...) APPLY(CAT_, a, CAT_5(__VA_ARGS__))
#define CAT_7(a, ...) APPLY(CAT_, a, CAT_6(__VA_ARGS__))
#define CAT_8(a, ...) APPLY(CAT_, a, CAT_7(__VA_ARGS__))
#define CAT(...) APPLY(CAT_, CAT_, COUNT(__VA_ARGS__))(__VA_ARGS__)

#define MAP_1(fn, a)      fn(a)
#define MAP_2(fn, a, ...) fn(a), MAP_1(fn, __VA_ARGS__)
#define MAP_3(fn, a, ...) fn(a), MAP_2(fn, __VA_ARGS__)
#define MAP_4(fn, a, ...) fn(a), MAP_3(fn, __VA_ARGS__)
#define MAP_5(fn, a, ...) fn(a), MAP_4(fn, __VA_ARGS__)
#define MAP_6(fn, a, ...) fn(a), MAP_5(fn, __VA_ARGS__)
#define MAP_7(fn, a, ...) fn(a), MAP_6(fn, __VA_ARGS__)
#define MAP_8(fn, a, ...) fn(a), MAP_7(fn, __VA_ARGS__)
#define MAP_9(fn, a, ...) fn(a), MAP_8(fn, __VA_ARGS__)
#define MAP_10(fn, a, ...) fn(a), MAP_9(fn, __VA_ARGS__)
#define MAP_11(fn, a, ...) fn(a), MAP_10(fn, __VA_ARGS__)
#define MAP_12(fn, a, ...) fn(a), MAP_11(fn, __VA_ARGS__)
#define MAP_13(fn, a, ...) fn(a), MAP_12(fn, __VA_ARGS__)
#define MAP_14(fn, a, ...) fn(a), MAP_13(fn, __VA_ARGS__)
#define MAP_15(fn, a, ...) fn(a), MAP_14(fn, __VA_ARGS__)
#define MAP_16(fn, a, ...) fn(a), MAP_15(fn, __VA_ARGS__)
#define MAP(fn, ...) CAT(MAP_, COUNT(__VA_ARGS__))(fn, __VA_ARGS__)

#define MAP_S_1(fn, a)      fn(a)
#define MAP_S_2(fn, a, ...) fn(a) MAP_S_1(fn, __VA_ARGS__)
#define MAP_S_3(fn, a, ...) fn(a) MAP_S_2(fn, __VA_ARGS__)
#define MAP_S_4(fn, a, ...) fn(a) MAP_S_3(fn, __VA_ARGS__)
#define MAP_S_5(fn, a, ...) fn(a) MAP_S_4(fn, __VA_ARGS__)
#define MAP_S_6(fn, a, ...) fn(a) MAP_S_5(fn, __VA_ARGS__)
#define MAP_S_7(fn, a, ...) fn(a) MAP_S_6(fn, __VA_ARGS__)
#define MAP_S_8(fn, a, ...) fn(a) MAP_S_7(fn, __VA_ARGS__)
#define MAP_S_9(fn, a, ...) fn(a) MAP_S_8(fn, __VA_ARGS__)
#define MAP_S_10(fn, a, ...) fn(a) MAP_S_9(fn, __VA_ARGS__)
#define MAP_S_11(fn, a, ...) fn(a) MAP_S_10(fn, __VA_ARGS__)
#define MAP_S_12(fn, a, ...) fn(a) MAP_S_11(fn, __VA_ARGS__)
#define MAP_S_13(fn, a, ...) fn(a) MAP_S_12(fn, __VA_ARGS__)
#define MAP_S_14(fn, a, ...) fn(a) MAP_S_13(fn, __VA_ARGS__)
#define MAP_S_15(fn, a, ...) fn(a) MAP_S_14(fn, __VA_ARGS__)
#define MAP_S_16(fn, a, ...) fn(a) MAP_S_15(fn, __VA_ARGS__)
#define MAP_S(fn, ...) CAT(MAP_S_, COUNT(__VA_ARGS__))(fn, __VA_ARGS__)

/* Simple math functions */
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC(n) CAT(INC_, n)

#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DEC_10 9
#define DEC_11 10
#define DEC_12 11
#define DEC_13 12
#define DEC_14 13
#define DEC_15 14
#define DEC_16 15
#define DEC_17 16
#define DEC(n) CAT(DEC_, n)

#endif
