#ifndef NE64BADGE_H
#define NE64BADGE_H

#include "mc9s12.h"
#include "io.h"

#include "ne64badge/config.h"
#include "ne64badge/memory.h"
#include "ne64badge/periph.h"

#define OSCCLK 25000

#define PE(n) BV(n)
#define PG(n) BV(n)
#define PH(n) BV(n)
#define PJ(n) BV(n)
#define PT(n) BV(n)
#define PAD(n) BV(n)

#define LED_PORT PTJ
#define LED1 PJ(0)
#define LED2 PJ(1)

#define BUTTON1_PORT PTE
#define BUTTON1 PE(0)

#define BUTTON2_PORT PTH
#define BUTTON2 PH(4)

#define GPIO_L PTG
#define GPIO0  PG(0)
#define GPIO1  PG(1)
#define GPIO2  PG(2)
#define GPIO3  PG(3)
#define GPIO4  PG(4)
#define GPIO5  PG(5)
#define GPIO6  PG(6)
#define GPIO7  PG(7)

#define GPIO_H PTT
#define GPIO8  PT(4)
#define GPIO9  PT(5)
#define GPIO10 PT(6)

#define ANALOG_IN0 PAD(1)
#define ANALOG_IN1 PAD(2)
#define ANALOG_IN2 PAD(3)
#define ANALOG_IN3 PAD(4)

#define XBEE_RESET  PH(2)
#define XBEE_RSSI   PH(3)
#define XBEE_LOAD_H PH(5)
#define XBEE_LOAD_L PH(6)

#define XBEE_TX TXD1
#define XBEE_RX RXD1

#define RS232_TX TXD0
#define RS232_RX RXD0

#endif
