#ifndef PERIPH_H
#define PERIPH_H

#include "io.h"
#include "macro.h"

/* $0000 - $000F Multiplexed External Bus Interface Module (MEBI) Map 1 of 3 */
sfrb(0x0000, PORTA);
sfrb(0x0001, PORTB);
sfrb(0x0002, DDRA);
sfrb(0x0003, DDRB);
sfrb(0x0008, PORTE);
sfrb(0x0009, DDRE);
sfrb(0x000A, PEAR, NOACCE, na0, PIPOE, NECLK, LSTRE, RDWE);
sfrb(0x000B, MODE, MODC, MODB, MODA, na0, IVIS, na1, EMK, EME);
sfrb(0x000C, PUCR, PUPKE, na0, na1, PUPEE, na2, na3, PUPBE, PUPAE);
sfrb(0x000D, RDRIV, RDPK, na0, na1, RDPE, na2, na3, RDPB, RDPA);
sfrb(0x000E, EBICTL, na0, na1, na2, na3, na4, na5, na6, ESTR);

/* $0010 - $0014 Module Mapping Control Module (MMC) Map 1 of 4 */
sfrb(0x0010, INITRM, na0, na1, na2, na3, (RAM, 5), na4, na5, RAMHAL);
sfrb(0x0011, INITRG, na0, na1, na2, na3, (REG, 4));
sfrb(0x0012, INITEE, na0, na1, na2, na3, (EE, 5), na4, na5, EEON);
sfrb(0x0013, MISC, na0, na1, na2, na3, na4, (EXSTR, 2), ROMHM, ROMON);
sfrb(0x0014, MTST0);

/* $0015 - $0016 Interrupt Module (INT) Map 1 of 2 */
sfrb(0x0015, ITCR, na0, na1, na2, WRTINT, na3, na4, na5, (ADR, 4));
sfrb(0x0016, ITEST, INTE, INTC, INTA, INT8, INT6, INT4, INT2, INT0);

/* $0017 - $0017 Module Mapping Control Module (MMC) Map 2 of 4 */
sfrb(0x0017, MTST1);

/* $001A - $001B Miscellaneous Peripherals */
sfrw(0x001A, PARTID);
sfrb(0x001A, PARTIDH);
sfrb(0x001B, PARTIDL);

/* $001C - $001D Module Mapping Control Module (MMC) Map 3 of 4 */
sfrb(0x001C, MEMSIZ0,
     REG_SW, na0, na1, (EEP_SW, 2), na2, na3, na4, (RAM_SW, 3));
sfrb(0x001D, MEMSIZ1, na0, (ROM_SW, 2), na1, na2, na3, na4, na5, (PAG_SW, 2));

/* $001E - $001E Multiplexed External Bus Interface Module (MEBI) Map 2 of 3 */
sfrb(0x001E, IRQCR, IRQE, IRQEN);

/* $001F - $001F Interrupt Module (INT) Map 2 of 2 */
sfrb(0x001F, HPRIO, na0, na1, na2, na3, na4, na5, (PSEL, 7));

/* $0020 - $002F Debug Module (DBG) Including BKP Map 1 of 1 */
sfrb(0x0020, DBGC1, DBGEN, ARM, TRGSEL, BEGIN, DBGBRK, na0, CAPMOD);
sfrb(0x0021, DBGSC, AF, BF, CF, na0, na1, na2, na3, (TRG, 4));
sfrw(0x0022, DBGTB);
sfrb(0x0022, DBGTBH);
sfrb(0x0023, DBGTBL);
sfrb(0x0024, DBGCNT, TBF, na0, na1, na2, na3, na4, na5, (CNT, 6));
sfrb(0x0025, DBGCCX, na0, (PAGSEL, 2), na1, na2, na3, na4, na5, (EXTCMP, 6));
sfrw(0x0026, DBGCC);
sfrb(0x0026, DBGCCH);
sfrb(0x0027, DBGCCL);
sfrb(0x0028, DBGC2, BKABEN, FULL, BDM, TAGAB, BKCEN, TAGC, RWCEN, RWC);
sfrb(0x0029, DBGC3, na0, (BKAMB, 2), na1, (BKBMB, 2), RWAEN, RWA, RWBEN, RWB);
sfrb(0x002A, DBGCAX, na0, (PAGSEL, 2), na1, na2, na3, na4, na5, (EXTCMP, 6));
sfrw(0x002B, DBGCA);
sfrb(0x002B, DBGCAH);
sfrb(0x002C, DBGCAL);
sfrb(0x002D, DBGCBX, na0, (PAGSEL, 2), na1, na2, na3, na4, na5, (EXTCMP, 6));
sfrw(0x002E, DBGCB);
sfrb(0x002E, DBGCBH);
sfrb(0x002F, DBGCBL);

/* $0030 - $0031 Module Mapping Control Module (MMC) Map 4 of 4 */
sfrb(0x0030, PPAGE);

/* $0032 - $0033 Multiplexed External Bus Interface Module (MEBI) Map 3 of 3 */
sfrb(0x0032, PORTK);
sfrb(0x0033, DDRK);

/* $0034 - $003F Clock and Reset Generator (CRG) */
sfrb(0x0034, SYNR);
sfrb(0x0035, REFDV);
sfrb(0x0036, CTFLG);
sfrb(0x0037, CRGFLG, RTIF, PORF, LVRF, LOCKIF, LOCK, TRACK, SCMIF, SCM);
sfrb(0x0038, CRGINT, RTIE, na0, na1, LOCKIE, na2, na3, SCMIE);
sfrb(0x0039, CLKSEL,
     PLLSEL, PSTP, SYSWAI, ROAWAI, PLLWAI, CWAI, RTIWAI, COPWAI);
sfrb(0x003A, PLLCTL, CME, PLLON, AUTO, ACQ, na0, PRE, PCE, SCME);
sfrb(0x003B, RTICTL);
sfrb(0x003C, COPCTL, WCOP, RSBCK, na0, na1, na2, na3, na4, (CR, 3));
sfrb(0x003D, FORBYP);
sfrb(0x003E, CTCTL);
sfrb(0x003F, ARMCOP);

/* $0040 - $006F 16-Bit, 4-Channel Timer Module (TIM) (Sheet 1 of 2) */
sfrb(0x0040, TIOS,  IOS7, IOS6, IOS5, IOS4, IOS3, IOS2, IOS1, IOS0);
sfrb(0x0041, CFORC, FOC7, FOC6, FOC5, FOC4, FOC3, FOC2, FOC1, FOC0);
sfrb(0x0042, OC7M);
sfrb(0x0043, OC7D);
sfrw(0x0044, TCNT);
sfrb(0x0044, TCNTH);
sfrb(0x0045, TCNTL);
sfrb(0x0046, TSCR1, TEN, TSWAI, TSFRZ, TFFCA);
sfrb(0x0047, TTOV);
sfrb(0x0048, TCTL1, OM7, OL7, OM6, OL6, OM5, OL5, OM4, OL4);
sfrb(0x004A, TCTL3, EDG7B, EDG7A, EDG6B, EDG6A, EDG5B, EDG5A, EDG4B, EDG4A);
sfrb(0x004C, TIE, C7I, C6I, C5I, C4I, C3I, C2I, C1I, C0I);
sfrb(0x004D, TSCR2, TOI, na0, na1, na2, TCRE, na3, na4, (PR, 3));
sfrb(0x004E, TFLG1, C7F, C6F, C5F, C4F, C3F, C2F, C1F, C0F);
sfrb(0x004F, TFLG2, TOF);
sfrw(0x0058, TC4);
sfrb(0x0058, TC4H);
sfrb(0x0059, TC4L);
sfrw(0x005A, TC5);
sfrb(0x005A, TC5H);
sfrb(0x005B, TC5L);
sfrw(0x005C, TC6);
sfrb(0x005C, TC6H);
sfrb(0x005D, TC6L);
sfrw(0x005E, TC7);
sfrb(0x005E, TC7H);
sfrb(0x005F, TC7L);
sfrb(0x0060, PACTL, na0, PAEN, PAMOD, PEDGE, na1, (CLK, 2), PAOVI, PAI);
sfrb(0x0061, PAFLG, na0, na1, na2, na3, na4, na5, PAOVF, PAIF);
sfrw(0x0062, PACNT);
sfrb(0x0062, PACNTH);
sfrb(0x0063, PACNTL);

/* $0080 - $009F 10-Bit, 8-Channel Analog-to-Digital Converter Module (ATD) */
sfrb(0x0080, ATDCTL0);
sfrb(0x0081, ATDCTL1,
     ETRIGSEL, na0, na1, na2, na3, ETRIGCH2, ETRIGCH1, ETRIGCH0);
sfrb(0x0082, ATDCTL2,
     ADPU, AFFC, AWAI, ETRIGLE, ETRIGGP, ETRIGE, ASCIE, ASCIF);
sfrb(0x0083, ATDCTL3, na0, S8C, S4C, S2C, S1C, FIFO, na1, (FRZ, 2));
sfrb(0x0084, ATDCTL4, SRES8, na0, (SMP, 2), na1, na2, na3, na4, (PRS, 5));
sfrb(0x0085, ATDCTL5, DJM, DSGN, SCAN, MULT, na0, CC, CB, CA);
sfrb(0x0086, ATDSTAT0, SCF, na0, ETORF, FIFOR, na1, na2, na3, (CC, 3));
sfrb(0x0088, ATDTEST0);
sfrb(0x0089, ATDTEST1, na0, na1, na2, na3, na4, na5, na6, SC);
sfrb(0x008B, ATDSTAT1);
sfrb(0x008D, ATDDIEN);
sfrb(0x008F, PORTAD);
sfrb(0x0090, ATDDR0H);
sfrb(0x0091, ATDDR0L);
sfrb(0x0092, ATDDR1H);
sfrb(0x0093, ATDDR1L);
sfrb(0x0094, ATDDR2H);
sfrb(0x0095, ATDDR2L);
sfrb(0x0096, ATDDR3H);
sfrb(0x0097, ATDDR3L);
sfrb(0x0098, ATDDR4H);
sfrb(0x0099, ATDDR4L);
sfrb(0x009A, ATDDR5H);
sfrb(0x009B, ATDDR5L);
sfrb(0x009C, ATDDR6H);
sfrb(0x009D, ATDDR6L);
sfrb(0x009E, ATDDR7H);
sfrb(0x009F, ATDDR7L);

/* $00C8 - $00CF Asynchronous Serial Communications Interface Module (SCI0) */
sfrw(0x00C8, SCI0BD);
sfrb(0x00C8, SCI0BDH);
sfrb(0x00C9, SCI0BDL);
sfrb(0x00CA, SCI0CR1);
sfrb(0x00CB, SCI0CR2);
sfrb(0x00CC, SCI0SR1);
sfrb(0x00CD, SCI0SR2);
sfrb(0x00CE, SCI0DRH);
sfrb(0x00CF, SCI0DRL);

/* $00D0 - $00D7 Asynchronous Serial Communications Interface Module (SCI1) */
sfrw(0x00D0, SCI1BD);
sfrb(0x00D0, SCI1BDH);
sfrb(0x00D1, SCI1BDL);
sfrb(0x00D2, SCI1CR1);
sfrb(0x00D3, SCI1CR2);
sfrb(0x00D4, SCI1SR1);
sfrb(0x00D5, SCI1SR2);
sfrb(0x00D6, SCI1DRH);
sfrb(0x00D7, SCI1DRL);

/* for both SCI0 and SCI1 */
regw(SCIBD, IREN, na0, (TNP, 2), na1, na2, na3, na4, na5, na6, na7, na8, na9, na10, na11, na12, (SBR, 13));
regb(SCIBDH, IREN, na0, (TNP, 2), na1, na2, na3, na4, (SBR, 5));
regb(SCIBDL, na0, na1, na2, na3, na4, na5, na6, (SBR, 8));
regb(SCICR1, LOOPS, SCISWAI, RSRC, M, WAKE, ILT, PE, PT);
regb(SCICR2, TIE, TCIE, RIE, ILIE, TE, RE, RWU, SBK);
regb(SCISR1, TDRE, TC, RDRF, IDLE, OR, NF, FE, PF);
regb(SCISR2, na0, na1, na2, na3, na4, BRK13, TXDIR, RAF);

/* $00D8 - $00DF Serial Peripheral Interface Module (SPI) */
sfrb(0x00D8, SPICR1, SPIE, SPE, SPTIE, MSTR, CPOL, CPHA, SSOE, LSBFE);
sfrb(0x00D9, SPICR2, na0, na1, na2, MODFEN, BIDIROE, na3, SPISWAI, SPC);
sfrb(0x00DA, SPIBR, na0, na1, na2, (SPPR, 3), na3, na4, na5, (SPR, 3));
sfrb(0x00DB, SPISR, SPIF, na0, SPTEF, MODF);
sfrb(0x00DD, SPIDR);

/* $00E0 - $00E7 Inter-IC Bus Module (IIC) */
sfrb(0x00E0, IBAD);
sfrb(0x00E1, IBFD);
sfrb(0x00E2, IBCR, IBEN, IBIE, MSSL, TXRX, TXAK, RSTA, na0, IBSWAI);
sfrb(0x00E3, IBSR, TCF, IAAS, IBB, IBAL, na0, SRW, IBIF, RXAK);
sfrb(0x00E4, IBDR);

/* $0100 - $010F FLASH Control Register (fts64k) */
sfrb(0x0100, FCLKDIV, FDIVLD, PRDIV8, na0, na1, na2, na3, na4, (FDIV, 6));
sfrb(0x0101, FSEC, KEYEN, na0, na1, na2, na3, (NV, 5), na4, (SEC, 2));
sfrb(0x0103, FCNFG, CBEIE, CCIE, KEYACC);
sfrb(0x0104, FPROT,
     FPOPEN, NV6, FPHDIS, na0, (FPHS, 2), FPLDIS, na1, (FPLS, 2));
sfrb(0x0105, FSTAT, CBEIF, CCIF, PVIOL, ACCERR, na0, BLANK);
sfrb(0x0106, FCMD);

/* $0120 - $0123 Ethernet Physical Transceiver Module (EPHY) */
sfrb(0x0120, EPHYCTL0,
     EPHYEN, ANDIS, DIS100, DIS10, LEDEN, EPHYWAI, na0, EPHYIEN);
sfrb(0x0121, EPHYCTL1);
sfrb(0x0122, EPHYSR, na0, na1, 100DIS, 10DIS, na2, na3, na4, EPHYIF);
sfrb(0x0123, EPHYTST);

/* $0140 - $016F Ethernet Media Access Controller (EMAC) */
sfrb(0x0140, NETCTL, EMACE, na0, na1, ESWAI, EXTPHY, MLB, FDX);
sfrb(0x0143, RXCTS, RXACT, na0, na1, RFCE, na2, PROM, CONMC, BCREJ);
sfrb(0x0144, TXCTS, TXACT, na0, CSLF, PTRC, SSB, na1, na2, (TCMD, 2));
sfrb(0x0145, ETCTL, FPET, na0, na1, FEMW, FIPV6, FARP, FIPV4, FIEEE);
sfrw(0x0146, ETYPE);
sfrb(0x0146, ETYPEH);
sfrb(0x0147, ETYPEL);
sfrw(0x0148, PTIME);
sfrb(0x0148, PTIMEH);
sfrb(0x0149, PTIMEL);
sfrw(0x014A, IEVENT,
     RFCIF, na0, BREIF, RXEIF, RXAOIF, RXBOIF, RXACIF, RXBCIF,
     MMCIF, na1,  LCIF,  ECIF,    na2,    na3,  TXCIF);
sfrb(0x014A, IEVENTH);
sfrb(0x014B, IEVENTL);
sfrw(0x014C, IMASK,
     RFCIE, na0, BREIE, RXEIE, RXAOIE, RXBOIE, RXACIE, RXBCIE,
     MMCIE, na1,  LCIE,  ECIE,    na2,    na3,  TXCIE);
sfrb(0x014C, IMASKH);
sfrb(0x014D, IMASKL);
sfrb(0x014E, SWRST, MACRST);
sfrb(0x0150, MPADR);
sfrb(0x0151, MRADR);
sfrw(0x0152, MWDATA);
sfrb(0x0152, MWDATAH);
sfrb(0x0153, MWDATAL);
sfrw(0x0154, MRDATA);
sfrb(0x0154, MRDATAH);
sfrb(0x0155, MRDATAL);
sfrb(0x0156, MCMST, na0, (OP, 2), BUSY, NOPRE, na1, na2, na3, (MDCSEL, 4));
sfrw(0x0158, BUFCFG,
     na0, na1, na2, (BUFMAP, 3), na3, na4, na5, na6,
     na7, na8, na9, na10, na11, na12, na13, (MAXFL, 11));
sfrb(0x0158, BUFCFGH);
sfrb(0x0159, BUFCFGL);
sfrw(0x015A, RXAEFP);
sfrb(0x015A, RXAEFPH);
sfrb(0x015B, RXAEFPL);
sfrw(0x015C, RXBEFP);
sfrb(0x015C, RXBEFPH);
sfrb(0x015D, RXBEFPL);
sfrw(0x015E, TXEFP);
sfrb(0x015E, TXEFPH);
sfrb(0x015F, TXEFPL);
sfrn(0x0160, MCHASH, 8);
sfrb(0x0160, MCHASH_START);
sfrb(0x0167, MCHASH_END);
sfrn(0x0168, MACAD, 8);
sfrb(0x0168, MACAD_START);
sfrb(0x016D, MACAD_END);
sfrw(0x016E, EMISC,
     na0, na1, (INDEX, 3), na2, na3, na4, na5, na6,
     na7, na8, na9, na10, na11, na12, na13, (MISC, 11));
sfrb(0x016E, EMISCH);
sfrb(0x016F, EMISCL);

/* $0240 - $026F Port Integration Module (PIM) (Sheet 1 of 3) */
sfrb(0x0240, PTT);
sfrb(0x0241, PTIT);
sfrb(0x0242, DDRT);
sfrb(0x0243, RDRT);
sfrb(0x0244, PERT);
sfrb(0x0245, PPST);
sfrb(0x0248, PTS);
sfrb(0x0249, PTIS);
sfrb(0x024A, DDRS);
sfrb(0x024B, RDRS);
sfrb(0x024C, PERS);
sfrb(0x024D, PPSS);
sfrb(0x024E, WOMS);
sfrb(0x0250, PTG);
sfrb(0x0251, PTIG);
sfrb(0x0252, DDRG);
sfrb(0x0253, RDRG);
sfrb(0x0254, PERG);
sfrb(0x0255, PPSG);
sfrb(0x0256, PIEG);
sfrb(0x0257, PIFG);
sfrb(0x0258, PTH);
sfrb(0x0259, PTIH);
sfrb(0x025A, DDRH);
sfrb(0x025B, RDRH);
sfrb(0x025C, PERH);
sfrb(0x025D, PPSH);
sfrb(0x025E, PIEH);
sfrb(0x025F, PIFH);
sfrb(0x0260, PTJ);
sfrb(0x0261, PTIJ);
sfrb(0x0262, DDRJ);
sfrb(0x0263, RDRJ);
sfrb(0x0264, PERJ);
sfrb(0x0265, PPSJ);
sfrb(0x0266, PIEJ);
sfrb(0x0267, PIFJ);
sfrb(0x0268, PTL);
sfrb(0x0269, PTIL);
sfrb(0x026A, DDRL);
sfrb(0x026B, RDRL);
sfrb(0x026C, PERL);
sfrb(0x026D, PPSL);
sfrb(0x026E, WOML);

#endif
