//
// Device initialization
//

#include "ne64badge.h"

INIT(init, INIT_DEV) {
    // enable flash memory
    MISC = MISC_ROMON;

    /**********************************************************************
     * basic clock configuration
     *
     * clock tree:
     * - PLLCLK = 2 * OSCCLK * (SYNR[5:0] + 1) / (REFDV[3:0] + 1)
     * - SYSCLK = PLLSEL ? PLLCLK : OSCCLK
     * - MCUCLK = SYSCLK      # clock for MCU
     * - BUSCLK = SYSCLK / 2  # clock for MCU bus and all modules
     * - PRDCLK = OSCCLK / (PRDIV8 ? 8 : 1)
     * - FCLK = PRDCLK / (1 + FDIV[5:0])   # Flash memory clock
     * - BDMCLK = PLLSEL ? (CLKSW ? ALTCLK : PLLCLK) : BUSCLK
     *
     * notes:
     * - FCLK must be 150kHz <= .. <= 200kHz
     * - BUSCLK must be <= 25MHz
     * - CLKSW can only be written over BDM, so BDMCLK is always BUSCLK.
     *
     * see also:
     * - "Figure 4-1. CRG Block Diagram" in MC9S12NE64V1.pdf
     * - "Figure 4-17. System Clocks Generator" in MC9S12NE64V1.pdf
     **********************************************************************/

    // for 25MHz BUSCLK with 25MHz OSC, SYSCLK must be PLL-generated
    SYNR   = 0;
    REFDV  = 0;
    PLLCTL = PLLCTL_PLLON|PLLCTL_AUTO;
    while (!(CRGFLG & CRGFLG_LOCK)); // wait for PLL gets locked (= stabilize)
    CLKSEL = CLKSEL_PLLSEL;

    /**********************************************************************
     * Flash memory configuration
     *
     * Configuration:
     * - Flash = ROM0 (16KB fixed) + ROM1 (16KB paged) + ROM2 (16KB fixed)
     * - Protected area in ROM0 is intended for EEPROM emulation.
     * - Protected area in ROM2 is intended for boot sector protection.
     * - Page size is 512B, and erase block size is 16KB.
     **********************************************************************/
    FCLKDIV = 125;                  // for 200KHz FCLK with 25MHz OSC
    FPROT   = FPROT_FPOPEN|FPROT_FPHDIS|FPROT_FPLDIS; // no protection at all

    /**********************************************************************
     * Timer configuration
     **********************************************************************/

    /**********************************************************************
     * SCI configuration
     *
     * NOTE:
     * - BAUDRATE = BUSCLK / ((IREN ? 32 : 16) * SBR[12:0])
     * - IREN is "InfraRed ENable" register
     * - max rate torelance = 4.63%
     **********************************************************************/

    // RS232
    SCI0BD  = 163;   // for 9600baud @ 25MHz BUSCLK
    SCI0CR1 = 0;     // 8N1
    SCI0CR2 = SCICR2_TE|SCICR2_RE; // Enable with no interrupt

    // XBEE
    SCI1BD  = 163;   // for 9600baud @ 25MHz BUSCLK
    SCI1CR1 = 0;     // 8N1
    SCI1CR2 = SCICR2_TE|SCICR2_RE; // Enable with no interrupt

    /**********************************************************************
     * IIC configuration
     *
     * NOTES:
     * - IICCLK = min load: BUSCLK / 20 or max load: 100Kbps
     * - max load = 400pF
     **********************************************************************/
    //IBAD = IIC_SLAVE_ARRESS;
    //IBFD = ...TBD...
    //IBCR = IBEN|..TBD..

    /**********************************************************************
     * ADC (ATD) configuration
     *
     * NOTES:
     * - ATDCLK must be 500KHz <= .. <= 2MHz
     **********************************************************************/

    /**********************************************************************
     * Ethernet configuration
     *
     * notes:
     * - MII_TXCLK must be 25MHz (100Mbps) or 2.5MHz (10Mbps)
     * - MII_RXCLK must be 25MHz (100Mbps) or 2.5MHz (10Mbps)
     **********************************************************************/

    /**********************************************************************
     * GPIO configuration
     **********************************************************************/
    DDRJ = 0xFF;

    /**********************************************************************
     * IRQ
     **********************************************************************/
    //INTCR |= IRQEN;
}
