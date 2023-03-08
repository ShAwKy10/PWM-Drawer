/**
 * @file    MTIMER_private.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com.com)
 * @brief   This file contains private information related to Timer module
 * @version 1.4
 * @date    2023-03-08
 * 
 * 
 */

/*Header file guard*/
#ifndef __MTIMER_PRIVATE_H__
#define __MTIMER_PRIVATE_H__

/**************************************************************************/
/*                          Timer registers                              */
/************************************************************************/

/*General timer registers*/
#define MTIMER_TIMSK            (*(volatile u8_t*)(0x59))
#define MTIMER_TIFR             (*(volatile u8_t*)(0x58))

/*Timer0 registers*/
#define MTIMER_TCCR0            (*(volatile u8_t*)(0x53))
#define MTIMER_TCNT0            (*(volatile u8_t*)(0x52))
#define MTIMER_OCR0             (*(volatile u8_t*)(0x5C))

/*Timer1 registers*/
#define MTIMER_TCCR1            (*(volatile u16_t*)(0x4E))
#define MTIMER_TCNT1            (*(volatile u16_t*)(0x4C))
#define MTIMER_OCR1A            (*(volatile u16_t*)(0x4A))
#define MTIMER_OCR1B            (*(volatile u16_t*)(0x48))
#define MTIMER_ICR1             (*(volatile u16_t*)(0x46))

/*Timer2 registers*/
#define MTIMER_TCCR2            (*(volatile u8_t*)(0x45))
#define MTIMER_TCNT2            (*(volatile u8_t*)(0x44))
#define MTIMER_OCR2             (*(volatile u8_t*)(0x43))

/********************************************************************************/
/*                          Timer registers' bits                              */
/******************************************************************************/

/*TCCR1 bits*/
#define MTIMER_TCCR1_ICES1_BIT         (6)

/*TIFR bits*/
#define MTIMER_TIFR_OCF0_BIT          (1)
#define MTIMER_TIFR_OCF1A_BIT         (4)
#define MTIMER_TIFR_OCF1B_BIT         (3)
#define MTIMER_TIFR_OCF2_BIT          (7)
#define MTIMER_TIFR_ICF1_BIT          (5)

/*TIMSK bits*/
#define MTIMER_TIMSK_OCIE0_BIT        (1)
#define MTIMER_TIMSK_OCIE1A_BIT       (4)
#define MTIMER_TIMSK_OCIE1B_BIT       (3)
#define MTIMER_TIMSK_OCIE2_BIT        (7)

#endif /*__MTIMER_PRIVATE_H__*/