/**
 * @file    MDIO_intrface.h
 * @author  Ahmed Shawky (amamasa121212@gamil.com)
 * @brief   This file contains interfacing information related to DIO module
 * @version 1.0
 * @date    2022-09-10
 * 
 * 
 * 
 */

/* Header file ground */
#ifndef __MDIO_INTERFACE_H__
#define __MDIO_INTERFACE_H__

/***************************************************************/
/*                   Interfacing macros                       */
/**************************************************************/

/*DIO Ports*/
#define PORTA           (0)
#define PORTB           (1)
#define PORTC           (2)
#define PORTD           (3)

/*DIO Pins*/
#define PIN0            (0b00000001)
#define PIN1            (0b00000010)
#define PIN2            (0b00000100)
#define PIN3            (0b00001000)
#define PIN4            (0b00010000)
#define PIN5            (0b00100000)
#define PIN6            (0b01000000)
#define PIN7            (0b10000000)

/*DIO Pins` Status*/
#define INPUT_FLOAT     (0)
#define INPUT_PULLUP    (1)
#define OUTPUT          (2)

/*DIO Pins` values*/
#define LOW             (0)
#define HIGH            (1)

/******************************************************************/
/*                   Functions` prototypes                        */
/******************************************************************/

/**
 * @brief This function is responsible for setting the DIO pins status (Input/Output)
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param au8_status 
 */
void mdio_SetPinStatus(u8_t au8_port, u8_t au8_pin, u8_t au8_status);

/**
 * @brief This function is responsible for setting the DIO pins value (High/Low)
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param au8_value
 */
void mdio_SetPinValue(u8_t au8_port, u8_t au8_pin, u8_t au8_value);

/**
 * @brief This function is responsible for toggling the DIO pins value (High -> Low/Low -> High)
 * 
 * @param au8_port 
 * @param au8_pin 
 */
void mdio_TogglePinValue(u8_t au8_port, u8_t au8_pin);

/**
 * @brief This function is responsible for getting the DIO pins value (High/Low)
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param pu8_pinValue 
 */
void mdio_GetPinValue(u8_t au8_port, u8_t au8_pin, u8_t* pu8_pinValue);

#endif