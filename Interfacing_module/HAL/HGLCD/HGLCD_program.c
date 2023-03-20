/**
 * @file    HGLCD_program.c
 * @author  Ahmed Shawky (amamasa121212@gamil.com)
 * @brief   This file contains logical implementation related to GLCD module
 * @version 3.4
 * @date    2023-03-20
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

#define NULL                   (0)
#define PAGE_INC_MACRO         (0.5)
#define SWITCH_HALF_OFSET      (64)
#define REMAIN_IN_THE_HALF     (200)

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
#define COLUMN_0               (0x40)
#define PAGE_0                 (0xB8)
#define START_LINE             (0xC0)

/*Numbers of pages,columns and start lines*/
#define TOTAL_PAGE             (8)
#define TOTAL_COLUMN           (128)

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
        hglcd_sendCommand((PAGE_0) + i); //Increment page

        for ( j = 0; j < 64; j++)
        {
            hglcd_sendData(NULL); //Write zeros to all 64 column

        }
         
    }
    
    hglcd_sendCommand(COLUMN_0);    //Set Y address (colmun = 0)
    hglcd_sendCommand(PAGE_0);      //Set X address (page = 0)

    /*Return from this function*/
    return;
}

void hglcd_displayString(u8_t au8_pageNum, u8_t au8_columnNum, u8_t* pu8_stringData)
{
    u8_t i, columnF;
    u8_t flag1 = 1;
    u8_t flag2;
    u16_t column = ((COLUMN_0) + au8_columnNum);
    u16_t page = ((PAGE_0) + au8_pageNum);
    u16_t Y_address = NULL;
    f32_t page_inc = PAGE_INC_MACRO;

    /*Select the half of display*/
    if (au8_columnNum < SWITCH_HALF_OFSET)
    {
        mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN, HIGH);
        mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN, LOW);
        hglcd_sendCommand(column);

        flag2 = SWITCH_HALF_OFSET - au8_columnNum;
    }
    else if (au8_columnNum >= SWITCH_HALF_OFSET)
    {
        mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN, LOW);
        mdio_SetPinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN, HIGH);
        hglcd_sendCommand(column - SWITCH_HALF_OFSET);

        flag2 = TOTAL_COLUMN - au8_columnNum;
    }
    
    hglcd_sendCommand(page);

    /*Print char in string till null*/
    for ( i = NULL; pu8_stringData[i] != NULL; i++)
    {
        if (((flag1 * FontWidth) >= flag2))
        {
            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);
            hglcd_sendCommand(COLUMN_0);
            hglcd_sendCommand(page);
            flag2 = REMAIN_IN_THE_HALF;
        }
        else
        {
            /*Do nothing*/
        }
        
        flag1++;

        if (Y_address > (1024 - (((au8_pageNum)* TOTAL_COLUMN) + FontWidth)))
        {
            break;
        }
        else
        {
            /*Do nothing*/
        }

        if (pu8_stringData[i] != 32)
        {
            for (columnF = 1; columnF <= FontWidth; columnF++)
            {
                if ((Y_address+columnF) == (TOTAL_COLUMN * ((u8_t)(page_inc + PAGE_INC_MACRO))))
                {
                    if (columnF == FontWidth)
                    {
                        break;
                    }
                    else
                    {
                        /*Do nothing*/
                    }

                    hglcd_sendCommand(COLUMN_0);
                    Y_address = Y_address + columnF;

                    mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                    mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                    hglcd_sendCommand(page + page_inc);
                    page_inc = page_inc + PAGE_INC_MACRO;

                }
                else
                {
                    /*Do nothing*/
                }

                if (Y_address > (1024 - (((au8_pageNum) * TOTAL_COLUMN) + FontWidth)))
                {
                    break;
                }
                else
                {
                    /*Do nothing*/
                }

                if ((font[((pu8_stringData [i] - 32) * FontWidth) + 4]) == 0 || pu8_stringData[i] == 32)
                {
                    for ( columnF = 0; columnF < FontWidth; columnF++)
                    {
                        hglcd_sendData(font[pu8_stringData[i] - 32][columnF]);

                        if ((Y_address + 1) % 64 == 0)
                        {
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                            hglcd_sendCommand(COLUMN_0);
                            hglcd_sendCommand((page + page_inc));
                            page_inc = page_inc + PAGE_INC_MACRO;
                        }
                        else
                        {
                            /*Do nothing*/
                        }
                        
                        Y_address++;
                        
                    }
                    
                }
                else
                {
                    for ( columnF = 0; columnF < FontWidth; columnF++)
                    {
                        hglcd_sendData(font[pu8_stringData[i] - 32][columnF]);

                        if ((Y_address + 1) % 64 == 0)
                        {
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                            mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                            hglcd_sendCommand(COLUMN_0);
                            hglcd_sendCommand((page + page_inc));
                            page_inc = page_inc + PAGE_INC_MACRO;
                        }
                        else
                        {
                            /*Do nothing*/
                        }
                        
                        Y_address ++;
                        
                    }

                    hglcd_sendData(0);
                    Y_address++;

                    if ((Y_address + 1) % 64 == 0)
                    {
                        mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS1_PIN);
                        mdio_TogglePinValue(LCD_CONTROL_LINES_PORT, LCD_CS2_PIN);

                        hglcd_sendCommand(COLUMN_0);
                        hglcd_sendCommand((page + page_inc));
                        page_inc = page_inc + PAGE_INC_MACRO;               
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
