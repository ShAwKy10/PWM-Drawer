/**
 * @file    LWDT.h
 * @author  Ahmed Ashraf (ahmedashrafelnaqeeb@gmail.com)
 * @brief   This file contatins the watch dog timer operaations
 * @version 1.0
 * @date    2022-10-15
 * 
 * 
 */

/*Header file guard*/
#ifndef __LWDT_H__
#define __LWDT_H__

/*WDT timeouts*/
#define TIMEOUT_16_3_MS             (0)
#define TIMEOUT_32_5_MS             (1)
#define TIMEOUT_65_MS               (2)
#define TIMEOUT_0_13_S              (3)
#define TIMEOUT_0_26_S              (4)
#define TIMEOUT_0_52_S              (5)
#define TIMEOUT_1_S                 (6)
#define TIMEOUT_2_1_S               (7)

/*WDT control register*/
#define MWDT_WDTCR                  (*(volatile u8_t*)(0x41))

/*WDT operations*/              
#define WDT_START(TIMEOUT)          MWDT_WDTCR = (0x08 | TIMEOUT)
#define WDT_REFRESH()               asm("wdr\r\n")
#define WDT_STOP()                  do                     \
                                    {                      \
                                        asm("wdr\r\n");    \
                                        MWDT_WDTCR = 0x18; \
                                        MWDT_WDTCR = 0;    \
                                    }while(0)

#endif /*__LWDT_H__*/