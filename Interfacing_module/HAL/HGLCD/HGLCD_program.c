/**
 * @file    HGLCD_program.c
 * @author  Ahmed Shawky (amamasa121212@gamil.com)
 * @brief   This file contains logical implementation related to GLCD module
 * @version 1.0
 * @date    2023-03-12
 * 
 * 
 * 
 */

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "Font_Header.h"
#include "MDIO_interface.h"
#include "HGLCD_cfg.h"
#include "HGLCD_interface.h"
#include "util/delay.h"

/***************************************************************************************************/
/*                                          Important macros                                       */
/***************************************************************************************************/

/*Data byte bits*/
#define BIT_0                  (0)
#define BIT_1                  (1)
#define BIT_2                  (2)
#define BIT_3                  (3)
#define BIT_4                  (4)
#define BIT_5                  (5)
#define BIT_6                  (6)
#define BIT_7                  (7)

/*LCD delay times in Milliseconds*/
#define POWER_ON_DELAY_MS      (20)
#define INSTRUCTION_DELAY_MS   (5)

/*DDRAM Address control header*/
#define DISPLAY_OFF            (0x3E)
#define COLUMN_0               (0x40)
#define PAGE_0                 (0xB8)
#define START_LINE             (0xC0)
#define DISPLAY_ON             (0x3F)

/*Numbers of pages*/
#define TOTAL_PAGE             (8)

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

static void hglcd_sendData(u8_t au8_data)
{
    /*Sending the data*/
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D0_PIN, GET_BIT(au8_data, BIT_0));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D1_PIN, GET_BIT(au8_data, BIT_1));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D2_PIN, GET_BIT(au8_data, BIT_2));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D3_PIN, GET_BIT(au8_data, BIT_3));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D4_PIN, GET_BIT(au8_data, BIT_4));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D5_PIN, GET_BIT(au8_data, BIT_5));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D6_PIN, GET_BIT(au8_data, BIT_6));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D7_PIN, GET_BIT(au8_data, BIT_7));

    /*Setting RS Pin to LOW to send data*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_RS_PIN, HIGH);

    /*Setting R/W Pin to LOW to write data over LCD*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_RW_PIN, LOW);

    /*Triggering the LCD MCU to read the written data*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_EN_PIN, HIGH);
    _delay_ms(INSTRUCTION_DELAY_MS);
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_EN_PIN, LOW);
    _delay_ms(INSTRUCTION_DELAY_MS);

    /*Return from this function*/
    return;
}

static void hglcd_sendCommand(u8_t au8_command)
{
    /*Sending the command*/
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D0_PIN, GET_BIT(au8_command, BIT_0));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D1_PIN, GET_BIT(au8_command, BIT_1));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D2_PIN, GET_BIT(au8_command, BIT_2));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D3_PIN, GET_BIT(au8_command, BIT_3));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D4_PIN, GET_BIT(au8_command, BIT_4));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D5_PIN, GET_BIT(au8_command, BIT_5));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D6_PIN, GET_BIT(au8_command, BIT_6));
    mdio_SetPinValue(LCD_DATA_LINES_PORT, LCD_D7_PIN, GET_BIT(au8_command, BIT_7));

    /*Setting RS Pin to LOW to send command*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_RS_PIN, LOW);

    /*Setting R/W Pin to LOW to write data over LCD*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_RW_PIN, LOW);

    /*Triggering the LCD MCU to read the written data*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_EN_PIN, HIGH);
    _delay_ms(INSTRUCTION_DELAY_MS);
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_EN_PIN, LOW);
    _delay_ms(INSTRUCTION_DELAY_MS);

    /*Return from this function*/
    return;
}

void hglcd_init(void)
{    
    /*Setting the LCD control lines to output*/
    mdio_SetPinStatus(LCD_CONTROL_LINES_PORT, (LCD_RS_PIN | LCD_RW_PIN | LCD_EN_PIN | LCD_RST_PIN | LCD_CS1_PIN | LCD_CS2_PIN), OUTPUT);

    /*Setting the LCD data lines to output*/
    mdio_SetPinStatus(LCD_DATA_LINES_PORT, (LCD_D0_PIN | LCD_D1_PIN | LCD_D2_PIN | LCD_D3_PIN | LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN), OUTPUT);

    /*Select both left and right half of display and keep rest pin high */
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, (LCD_CS1_PIN | LCD_CS2_PIN | LCD_RST_PIN ), HIGH);
    
    _delay_ms(POWER_ON_DELAY_MS);
    hglcd_sendCommand(DISPLAY_OFF);     //Display off
    hglcd_sendCommand(COLUMN_0);        //Set Y address(clomun = 0)
    hglcd_sendCommand(PAGE_0);          //Set X address(page = 0) 
    hglcd_sendCommand(START_LINE);      //Set Z address(start line = 0)
    hglcd_sendCommand(DISPLAY_ON);      //Display on

    /*Return from this function*/
    return;
}

void hglcd_clearAll()
{
    u8_t i , j;

    /*Select both left and right half of display*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, (LCD_CS1_PIN | LCD_CS2_PIN), HIGH);

    for ( i = 0; i < TOTAL_PAGE; i++)
    {
        hglcd_sendCommand((0xB0) + i); //Increment page

        for ( j = 0; j < 64; j++)
        {
            hglcd_sendData(0); //Write zeros to all 64 column

        }
         
    }
    
    hglcd_sendCommand(COLUMN_0);    //Set Y address (colmun = 0)
    hglcd_sendCommand(PAGE_0);      //Set X address (page = 0)

    /*Return from this function*/
    return;
}

void hglcd_displayString(u8_t au8_pageNum, u8_t* pu8_stringData)
{
    u8_t i , column;
    u16_t page = ((0x0B) + au8_pageNum);
    u16_t Y_address = 0;
    f32_t page_inc = 0.5;

    /*Select left half of display*/
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN, HIGH);
    mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN, LOW);

    hglcd_sendCommand(page);

    /*Print char in string till null*/
    for ( i = 0; pu8_stringData[i] != 0; i++)
    {
        if (Y_address > (1024 - (((au8_pageNum)* 128) + FontWidth)))
        {
            break;;
        }
        else
        {
            /*Do nothing*/
        }

        if (pu8_stringData[i] != 32)
        {
            for (column = 1; column <= FontWidth; column++)
            {
                if ((Y_address+column) == (128 * ((u8_t)(page_inc + 0.5))))
                {
                    if (column == FontWidth)
                    {
                        break;
                    }
                    else
                    {
                        /*Do nothing*/
                    }
                    
                    hglcd_sendCommand(COLUMN_0);
                    Y_address = Y_address + column;

                    mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                    mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                    hglcd_sendCommand(page + page_inc);
                    page_inc = page_inc + 0.5;

                }
                else
                {
                    /*Do nothing*/
                }

                if (Y_address > (1024 - (((au8_pageNum) * 128) + FontWidth)))
                {
                    break;
                }
                else
                {
                    /*Do nothing*/
                }

                if ((font[((pu8_stringData [i] - 32) * FontWidth) + 4]) == 0 || pu8_stringData[i] == 32)
                {
                    for ( column = 0; column < FontWidth; column++)
                    {
                        hglcd_sendData(font[pu8_stringData[i] - 32][column]);

                        if ((Y_address + 1) % 64 == 0)
                        {
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                            hglcd_sendCommand((page + page_inc));
                            page_inc = page_inc + 0.5;
                        }
                        else
                        {
                            /*Do nothing*/
                        }
                        
                        Y_address ++;
                        
                    }
                    
                }
                else
                {
                    for ( column = 0; column < FontWidth; column++)
                    {
                        hglcd_sendData(font[pu8_stringData[i] - 32][column]);

                        if ((Y_address + 1) % 64 == 0)
                        {
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                            hglcd_sendCommand((page + page_inc));
                            page_inc = page_inc + 0.5;
                        }
                        else
                        {
                            /*Do nothing*/
                        }
                        
                        Y_address ++;
                        
                    }

                    hglcd_sendData(0);
                    Y_address ++;

                    if ((Y_address + 1) % 64 == 0)
                    {
                        mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                        mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                        hglcd_sendCommand((page + page_inc));
                        page_inc = page_inc + 0.5;               
                    }
                    
                }
                  
            }
            
        }
        else
        {
            /*Do nothing*/
        }  
        
    }

    hglcd_sendCommand(COLUMN_0); //Set Y address (column = 0)
    
    /*Return from this function*/
    return;
}

void hglcd_displayImage(u8_t* pu8_pxl)
{

    /*Return from this function*/
    return;
}
