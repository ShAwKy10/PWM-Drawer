/**
 * @file    MTIMER_cfg.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com.com)
 * @brief   This file contains configuration information related to Timer module
 * @version 1.0
 * @date    2023-03-06
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

/*Clear to compare mode 1 ms delay*/
#define TIMER_1_MS_DELAY                (250)

#endif /*__MTIMER_CFG_H__*/