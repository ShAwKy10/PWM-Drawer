/**
 * @file    MTIMER_cfg.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com.com)
 * @brief   This file contains configuration information related to Timer module
 * @version 1.4
 * @date    2023-03-08
 * 
 * 
 */

/*Header file guard*/
#ifndef __MTIMER_CFG_H__
#define __MTIMER_CFG_H__

/*******************************************************************************/
/*                          Configuration macros                              */
/*****************************************************************************/

/*Custom prescaler choice*/
#define TIMER_OPERATION_STOP            (0xF8)
#define TIMER1_OPERATION_STOP           (0xFFF8)

/*ICU frequency value*/
#define TIMER_ICU_FREQ_4_US_DIVIDER     (250000)
#define TIMER_ICU_FREQ_0_5_US_DIVIDER   (2000000)

/*Clear to compare mode 1 ms delay*/
#define TIMER_1_MS_DELAY                (250)

#endif /*__MTIMER_CFG_H__*/