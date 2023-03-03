/**
 * @file    LBIT_MATH.h
 * @author  Ahmed Shawky (amamasa121212@gmail.com)
 * @brief   This file contains the bits` mathematics macros
 * @version 1.0
 * @date    2022-09-10
 * 
 *
 * 
 */

/* Header file ground */
#ifndef __LBIT_MATH_H__
#define __LBIT_MATH_H__

/* Bit manipulation operations */
#define SET_BIT(REG, BIT)       (REG |= (1 <<  BIT))
#define CLEAR_BIT(REG, BIT)     (REG &= ~(1 <<  BIT))
#define TOGGLE_BIT(REG, BIT)    (REG ^= (1 <<  BIT))
#define GET_BIT(REG, BIT)       ((REG >>  BIT) & 0x1)

#endif