/**
 * @file    MTIMER_interface.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com.com)
 * @brief   This file contains interfacing information related to Timer module
 * @version 1.0
 * @date    2023-03-05
 * 
 * 
 */

/*Header file guard*/
#ifndef __MTIMER_INTERFACE_H__
#define __MTIMER_INTERFACE_H__

/*****************************************************************************/
/*                          Interfacing macros                              */
/***************************************************************************/

/*Timer channels*/
#define TIMER_CHANNEL_0                     (0)
#define TIMER_CHANNEL_1                     (1)
#define TIMER_CHANNEL_2                     (2)

/*Timer prescalers*/
#define TIMER_PRESCALER_1                   (1)
#define TIMER_PRESCALER_8                   (2)
#define TIMER_PRESCALER_64                  (3)
#define TIMER_PRESCALER_256                 (4)
#define TIMER_PRESCALER_1024                (5)

/*Timer modes*/
#define TIMER_DELAY_MODE                    (0x08)

/*Timer prescalers*/
#define TIMER_DELAY_PRESCALER               (TIMER_PRESCALER_64)

/*Timer asynchronous modes*/
#define Timer_SINGLE_OPERATION              (0)
#define Timer_PERIODIC_OPERATION            (1)

/********************************************************************************/
/*                          Functions' prototypes                              */
/******************************************************************************/

/**
 * @brief This function is responsible for initializing specific timer channel (0/1/2) with certain mode and prescaler
 * 
 * @param au8_timerChannel 
 * @param timerMode 
 * @param timerPrescaler 
 */
void mtimer_init(u8_t au8_timerChannel, u8_t au8_timerMode, u8_t au8_timerPrescaler);

/**
 * @brief This function is responsible for creating delay in ms by using synchronous operation
 * 
 * @param au8_timerChannel 
 * @param au32_delayTime_ms 
 */
void mtimer_delayMs_synchronous(u8_t au8_timerChannel,u32_t au32_delayTime_ms);

/**
 * @brief This function is responsible for creating delay in ms by using asynchronous operation (periodic / non-periodic)
 * 
 * @param au8_timerChannel 
 * @param au32_delayTime_ms 
 * @param fptr_operationPointer 
 * @param au8_operationType 
 */
void mtimer_delayMs_asynchronous(u8_t au8_timerChannel,u32_t au32_delayTime_ms, void (*fptr_operationPointer)(void), u8_t au8_operationType);

#endif /*__MTIMER_INTERFACE_H__*/