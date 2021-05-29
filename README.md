# ne64 - Development environment for MC68HCS12NE64

This is an effort to revive development environment for MC68HCS12NE64,
using NE64 Badge board from Future Electronics.

NE64 Board comes with fairly modern configuration with following chips/devices:

- MC68HCS12 NE64 16-bit microcontroller
  - 3.3V VCC/IO
  - On-chip 100Ethernet PHY/MAC
  - 64KB Flash, 8KB SRAM
    - Can support up to 4MB memory with banking
  - 8ch 10bit ADC
  - 4ch 16-bit timers
  - I2C, SPI, and 2ch SCI/UART
- On-board devices
  - 2 user buttons
  - 2 user LEDs
  - 6 power and ethernet-driven LEDs
  - PoE-enabled RJ45 port
  - RS232 UART (connected to UART0)
  - MaxStream XBee socket (connected to UART1)
  - 40x2 pin header with UART/SPI/I2C/GPIO and external memory interface

## Project contents

Followings are currently available:

- register definition macros
- board configuration macros
- linker script
- sample code (LED blink + UART)

Toolchain is not self-hosted yet and I'm still using prebuilt m9s12x-gcc/binutils binaries
I obtained from fairly reliable source (but forgot where it was).

For programmer/debugger, USBDM is expected to be used.

## Setup

```
make -C lib
make -C hello
```

Building under lib generates C startup file object and linker scripts.
This is only needed once, unless you modify them.

## TODO

Due to memory banking, toolchain/linker/programmer/debugger must
agree/align on what VMA to be given to symbols in object file when
it is placed in banked segment that maps above 64KB address space.

I'm not yet certain that I have figured/sorted all out, so there
may be some (or many) gotchas.
