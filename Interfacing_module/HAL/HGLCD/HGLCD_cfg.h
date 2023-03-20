/**
 * @file    HGLCD_cfg.h
 * @author  Ahmed Shawky (amamasa121212@gamil.com)
 * @brief   This file contains configuration information related to GLCD module
 * @version 1.1
 * @date    2022-03-20
 * 
 * 
 * 
 */

/*Header file guard*/
#ifndef __HGLCD_CFG_H__
#define __HGLCD_CFG_H__

/***************************************************************************************************/
/*                                         Configuration macros                                    */
/***************************************************************************************************/

/*LCD Control lines configurations*/
#define LCD_CONTROL_LINES_PORT      (PORTC)
#define LCD_RS_PIN                  (PIN0)
#define LCD_RW_PIN                  (PIN1)
#define LCD_EN_PIN                  (PIN2)
#define LCD_RST_PIN                 (PIN3)
#define LCD_CS1_PIN                 (PIN4)
#define LCD_CS2_PIN                 (PIN5)

/*LCD Data lines configurations*/
#define LCD_DATA_LINES_PORT         (PORTA)
#define LCD_D0_PIN                  (PIN0)
#define LCD_D1_PIN                  (PIN1)
#define LCD_D2_PIN                  (PIN2)
#define LCD_D3_PIN                  (PIN3)
#define LCD_D4_PIN                  (PIN4)
#define LCD_D5_PIN                  (PIN5)
#define LCD_D6_PIN                  (PIN6)
#define LCD_D7_PIN                  (PIN7)

/*LCD Instructions*/
#define DISPLAY_ON                  (0x3F)
#define DISPLAY_OFF                 (0x3E)

#endif /*__HGLCD_CFG_H__*/