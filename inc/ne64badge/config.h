#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_BUFMAP 0

#ifdef CONFIG_BUFMAP
#if CONFIG_BUFMAP == 4
#define RXTX_BUFSIZE 1536
#else
#define RXTX_BUFSIZE (128 << (CONFIG_BUFMAP))
#endif
#ifndef __ASSEMBLER__
extern volatile char RXBUF_A[RXTX_BUFSIZE] asm("__RXBUF_A");
extern volatile char RXBUF_B[RXTX_BUFSIZE] asm("__RXBUF_B");
extern volatile char   TXBUF[RXTX_BUFSIZE] asm("__TXBUF");
#endif
#endif

#endif
