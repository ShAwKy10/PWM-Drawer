/**
 * @file    MTIMER_interface.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com.com)
 * @brief   This file contains logical imprlementaion related to Timer module
 * @version 1.0
 * @date    2023-03-05
 * 
 * 
 */

/*Header file guard*/
#ifndef __MTIMER_PROGRAM_C__
#define __MTIMER_PROGRAM_C__

/*******************************************************************/
/*                          Includes                              */
/*****************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "avr/interrupt.h"
#include "MTIMER_private.h"
#include "MTIMER_cfg.h"
#include "MTIMER_interface.h"

/***************************************************************************/
/*                          Important macros                              */
/*************************************************************************/

#define NULL                ((void*)0)

/******************************************************************************/
/*                          Important variables                              */
/****************************************************************************/

/*Global variables used to set timer prescaler*/
static u8_t gu8_timer0_prescaler;
static u8_t gu8_timer1_prescaler;
static u8_t gu8_timer2_prescaler;

/*Global variables used to store the delay time in ms*/
static u32_t gu32_delayTimeMs_timer0;
static u32_t gu32_delayTimeMs_timer1;
static u32_t gu32_delayTimeMs_timer2;

/*Global pointers to function variables used to store the timers callback functions*/
static void (*gfptr_timer0ISR)(void) = NULL;
static void (*gfptr_timer1ISR)(void) = NULL;
static void (*gfptr_timer2ISR)(void) = NULL;

/*Global variables used to set timer asynchromous operation mode*/
static u8_t gu8_timer0_operation;
static u8_t gu8_timer1_operation;
static u8_t gu8_timer2_operation;

/*********************************************************************************/
/*                          Functions' definitions                              */
/*******************************************************************************/

static void mtimer_start(u8_t au8_timerChannel)
{
    /*Switching over timer channels*/
    switch (au8_timerChannel)
    {
        /*In case of channel 0*/
    case (TIMER_CHANNEL_0):

        /*Reset the timer counter0*/
        MTIMER_TCNT0 = 0;

        /*Setting the timer0 prescaler and its start operation*/
        MTIMER_TCCR0 |= gu8_timer0_prescaler;
        
        /*Breaking from this case*/
        break;

        /*In case of channel 1*/
    case (TIMER_CHANNEL_1):

        
        /*Breaking from this case*/
        break; 

        /*In case of channel 2*/
    case (TIMER_CHANNEL_2):

        
        /*Breaking from this case*/
        break; 

        /*In case of defult*/
    default:
        /*Breaking from this case*/
        break;
    }

    /*Return from this function*/
    return;
}

static void mtimer_stop(u8_t au8_timerChannel)
{
    /*Switching over timer channels*/
    switch (au8_timerChannel)
    {
        /*In case of channel 0*/
    case (TIMER_CHANNEL_0):

        /*Stop Timer0 operation*/
        MTIMER_TCCR0 &= TIMER_OPERATION_STOP;
        
        /*Breaking from this case*/
        break;

        /*In case of channel 1*/
    case (TIMER_CHANNEL_1):

        
        /*Breaking from this case*/
        break; 

        /*In case of channel 2*/
    case (TIMER_CHANNEL_2):

        
        /*Breaking from this case*/
        break; 

        /*In case of defult*/
    default:
        /*Breaking from this case*/
        break;
    }

    /*Return from this function*/
    return;
}

void mtimer_init(u8_t au8_timerChannel, u8_t au8_timerMode, u8_t au8_timerPrescaler)
{   
    /*Switching over timer channels*/
    switch (au8_timerChannel)
    {
        /*In case of channel 0*/
    case (TIMER_CHANNEL_0):

        /*Setting timer0 mode*/
        MTIMER_TCCR0 =  au8_timerMode;

        /*Setting the selected timer prescaler*/
        gu8_timer0_prescaler = au8_timerPrescaler;

        /*Breaking from this case*/
        break;

        /*In case of channel 1*/
    case (TIMER_CHANNEL_1):

        /*Setting timer1 mode*/
        MTIMER_TCCR0 =  au8_timerMode;

        /*Setting the selected timer prescaler*/
        gu8_timer1_prescaler = au8_timerPrescaler;

        /*Breaking from this case*/
        break; 

        /*In case of channel 2*/
    case (TIMER_CHANNEL_2):

        /*Setting timer2 mode*/
        MTIMER_TCCR0 =  au8_timerMode;

        /*Setting the selected timer prescaler*/
        gu8_timer2_prescaler = au8_timerPrescaler;

        /*Breaking from this case*/
        break; 

        /*In case of defult*/
    default:
        /*Breaking from this case*/
        break;
    }

    /*Return from this function*/
    return;    
}

void mtimer_delayMs_synchronous(u8_t au8_timerChannel,u32_t au32_delayTime_ms)
{
    /*Switching over timer channels*/
    switch (au8_timerChannel)
    {
        /*In case of channel 0*/
    case (TIMER_CHANNEL_0):

        /*Setting OCR0 value to make a compare match after 1 ms*/
        MTIMER_OCR0 = TIMER_1_MS_DELAY;

        /*Start the timer operation*/
        mtimer_start(TIMER_CHANNEL_0);

        /*Looping over delay value*/
        while (au32_delayTime_ms --)
        {
            /*Waitting until the 1ms delay over*/
            while (!GET_BIT(MTIMER_TIFR, MTIMER_TIFR_OCF0_BIT));

            /*Clearing the flag bit*/
            SET_BIT(MTIMER_TIFR, MTIMER_TIFR_OCF0_BIT);
            
        }

        /*Stoppping the timer operation*/
        mtimer_stop(TIMER_CHANNEL_0);
        
        /*Breaking from this case*/
        break;

        /*In case of channel 1*/
    case (TIMER_CHANNEL_1):

        
        /*Breaking from this case*/
        break; 

        /*In case of channel 2*/
    case (TIMER_CHANNEL_2):

        
        /*Breaking from this case*/
        break; 

        /*In case of defult*/
    default:
        /*Breaking from this case*/
        break;
    }

    /*Return from this function*/
    return;
}

void mtimer_delayMs_asynchronous(u8_t au8_timerChannel,u32_t au32_delayTime_ms, void (*fptr_operationPointer)(void), u8_t au8_operationType)
{
    /*Switching over timer channels*/
    switch (au8_timerChannel)
    {
        /*In case of channel 0*/
    case (TIMER_CHANNEL_0):

        /*Setting OCR0 value to make a compare match after 1 ms*/
        MTIMER_OCR0 = TIMER_1_MS_DELAY;

        /*Setting timer0 operation paremeters*/
        gu32_delayTimeMs_timer0 = au32_delayTime_ms;
        gfptr_timer0ISR = fptr_operationPointer;
        gu8_timer0_prescaler = au8_operationType;

        /*Enable output compare match interrupt*/
        SET_BIT(MTIMER_TIMSK, MTIMER_TIMSK_OCIE0_BIT);

        /*Start the timer operation*/
        mtimer_start(TIMER_CHANNEL_0);

        /*Breaking from this case*/
        break;

        /*In case of channel 1*/
    case (TIMER_CHANNEL_1):

        /*Setting timer1 operation paremeters*/
        gu32_delayTimeMs_timer1 = au32_delayTime_ms;
        gfptr_timer1ISR = fptr_operationPointer;
        gu8_timer1_prescaler = au8_operationType;

        /*Start the timer operation*/
        mtimer_start(TIMER_CHANNEL_1);
        
        /*Breaking from this case*/
        break; 

        /*In case of channel 2*/
    case (TIMER_CHANNEL_2):

        /*Setting timer2 operation paremeters*/
        gu32_delayTimeMs_timer2 = au32_delayTime_ms;
        gfptr_timer2ISR = fptr_operationPointer;
        gu8_timer2_prescaler = au8_operationType;

        /*Start the timer operation*/
        mtimer_start(TIMER_CHANNEL_2);
        
        /*Breaking from this case*/
        break; 

        /*In case of defult*/
    default:
        /*Breaking from this case*/
        break;
    }

    /*Return from this function*/
    return;
}


/***************************************************************/
/*                          ISRs                              */
/*************************************************************/

/*Timer0 ISR*/
ISR(TIMER0_COMP_vect)
{
    
    /*Static local variable used to trackthe delay time*/
    static u32_t au32_delayTemp = 0;

    /*Increment the delay variable*/
    au32_delayTemp++;

    /*Cheaking if the delay time has passed or not*/
    if (au32_delayTemp == gu32_delayTimeMs_timer0)
    {
        /*Checking if the callback function is valid or not*/
        if (gfptr_timer0ISR != NULL)
        {

            if (gu32_delayTimeMs_timer0 == 0)
            {
                /*Executing timer0 ISR callback function*/
                gfptr_timer0ISR();

                /*Reset the delay variable*/
                au32_delayTemp = 0;

                /*Checking if the timer is in single mode operation or not*/
                if (gu8_timer0_operation == Timer_SINGLE_OPERATION)
                {
                    /*Stopping timer0*/
                    mtimer_stop(TIMER_CHANNEL_0);
                }
                else
                {
                    /*Do nothing*/
                }
                
                
            }
            
        }
        else
        {
            /* Do nothing */
        }

    }

    else
    {
        /*Do nothing*/
    }
        

}

#endif /*__MTIMER_PROGRAM_C__*/