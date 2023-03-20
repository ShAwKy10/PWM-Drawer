/**
 * @file    HGLCD_intrface.h
 * @author  Ahmed Shawky (amamasa121212@gamil.com)
 * @brief   This file contains interfacing information related to GLCD module
 * @version 1.1
 * @date    2022-03-20
 * 
 * 
 * 
 */

/*Header file guard*/
#ifndef __HGLCD_INTERFACE_H__
#define __HGLCD_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This function is used to initialize the LCD module
 * 
 */
void hglcd_init(void);

/**
 * @brief This function is used to clear the LCD
 * 
 */
void hglcd_clearAll();

/**
 * @brief This function is used to display single character over LCD
 * 
 * @param pu8_characterData 
 */
void hglcd_displayCharacter(u8_t* pu8_characterData, u8_t au8_pn);

/**
 * @brief This function is responsible for displaying a string over LCD
 * 
 * @param pu8_stringData 
 * @param au8_pageNum 
 * @param au8_columnNum
 */
void hglcd_displayString(u8_t au8_pageNum, u8_t au8_columnNum, u8_t* pu8_stringData);

#endif /*__HGLCD_INTERFACE_H__*/