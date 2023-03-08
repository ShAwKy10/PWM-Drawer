/**
 * @file    MTIMER_interface.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com.com)
 * @brief   This file contains interfacing information related to Timer module
 * @version 1.1
 * @date    2023-03-07
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
#define TIMER_PWM_MODE                      (0x68)//Fast PWM mode by default
#define TIMER_ICU_MODE                      (0x0000)//ICU edge select is falling edge by default

/*Timer delay prescalers*/
#define TIMER_DELAY_PRESCALER               (TIMER_PRESCALER_64)

/*Timer PWM frequencies*/
#define TIMER_PH_CORRECT_OFFSET             (50)
#define TIMER_FREQ_30_HZ                    (TIMER_PRESCALER_1024 + TIMER_PH_CORRECT_OFFSET)
#define TIMER_FREQ_60_HZ                    (TIMER_PRESCALER_1024)
#define TIMER_FREQ_122_HZ                   (TIMER_PRESCALER_256 + TIMER_PH_CORRECT_OFFSET)
#define TIMER_FREQ_244_HZ                   (TIMER_PRESCALER_256)
#define TIMER_FREQ_500_HZ                   (TIMER_PRESCALER_64 + TIMER_PH_CORRECT_OFFSET)
#define TIMER_FREQ_1_KHZ                    (TIMER_PRESCALER_64)
#define TIMER_FREQ_3_9_KHZ                  (TIMER_PRESCALER_8 + TIMER_PH_CORRECT_OFFSET)
#define TIMER_FREQ_7_8_KHZ                  (TIMER_PRESCALER_8)
#define TIMER_FREQ_31_25_KHZ                (TIMER_PRESCALER_1 + TIMER_PH_CORRECT_OFFSET)
#define TIMER_FREQ_62_5_KHZ                 (TIMER_PRESCALER_1)

/*Timer ICU prescaler*/
#define TIMER_ICU_PRESCALER                 (TIMER_PRESCALER_64)

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
 * @param au16_timerMode 
 * @param au8_timerPrescaler 
 */
void mtimer_init(u8_t au8_timerChannel, u16_t au16_timerMode, u8_t au8_timerPrescaler);

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

/**
 * @brief This function is responsible for running PWM signal mode with pre-defined frequancy and certain duty cycle
 * 
 * @param au8_timerChannel 
 * @param au8_dutyCycle 
 */
void mtimer_runPWM_signal(u8_t au8_timerChannel, u8_t au8_dutyCycle);

/**
 * @brief This function is used to start a PWM signal
 * 
 * @param au8_timerChannel
 */
void mtimer_startPWM_signal(u8_t au8_timerChannel);

/**
 * @brief This function is used to stop a running PWM signal
 * 
 * @param au8_timerChannel
 */
void mtimer_stopPWM_signal(u8_t au8_timerChannel);

/**
 * @brief This function is used to get duty cycle and frequency of PWM signal
 * 
 * @param pu8_duty 
 * @param pu32_freq 
 */
void mtimer_getSignal_duty_and_freq(u8_t* pu8_duty, u32_t* pu32_freq);

#endif /*__MTIMER_INTERFACE_H__*/