#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "HGLCD_interface.h"
#include "MTIMER_interface.h"
#include "util/delay.h"
#include "stdio.h"
#include "string.h"

int main (void)
{
    u8_t i = 0;
    u8_t counter1;
    u8_t counter2;
    u8_t loopV1;
    u8_t loopV2;
    u8_t pageD = 7;
    u8_t pageM1 = 6;
    u8_t pageM2 = 7;
    u8_t pageU = 5;
    u8_t duty;
    f32_t time;    
    u32_t freq;

    u8_t str_duty[100];
    u8_t str_freq[100];
    u8_t str_time[100];

    mdio_SetPinStatus(PORTB, PIN3, OUTPUT);
    mdio_SetPinStatus(PORTD, PIN6, INPUT_FLOAT);

    mtimer_init(TIMER_CHANNEL_0, TIMER_PWM_MODE, TIMER_FREQ_1_KHZ);
    mtimer_init(TIMER_CHANNEL_1, TIMER_ICU_MODE, TIMER_ICU_PRESCALER);

    mtimer_startPWM_signal(TIMER_CHANNEL_0);
    mtimer_runPWM_signal(TIMER_CHANNEL_0, 128);

    hglcd_init();
    hglcd_clearAll();

    while (1)
    {
        hglcd_clearAll();

        mtimer_getSignal_duty_and_freq(&duty, &freq);

        _delay_ms(1000);

        time = (1/((f32_t)freq) * 1000000);

        sprintf((char*)str_duty, "%d", duty);
        sprintf((char*)str_freq, "%ld", freq);
        sprintf((char*)str_time, "%ld", (u32_t)time);

        hglcd_displayString(0, 0, (u8_t*)"Frequency:");
        hglcd_displayString(0, 64, (u8_t*)str_freq);
        hglcd_displayString(0, 100, (u8_t*)"Hz");

        hglcd_displayString(1, 0,(u8_t*)"Duty Cycle:");
        hglcd_displayString(1, 64, (u8_t*)str_duty);
        hglcd_displayString(1, 77, (u8_t*)"%");

        hglcd_displayString(2, 0,(u8_t*)"Time:");
        hglcd_displayString(2, 64, (u8_t*)str_time);
        hglcd_displayString(2, 100, (u8_t*)"us");     

        counter1 = duty / 10;
        counter2 = 10 - counter1;

        for ( i = 0; i < 128; i+=5)
        {
            for ( loopV1 = 0; loopV1 < counter2; loopV1++)
            {
                hglcd_displayString(pageD, i, (u8_t*)"_");
                i+=5;
                _delay_ms(500);
            }

            hglcd_displayString(pageM1, i, (u8_t*)"|");
            hglcd_displayString(pageM2, i, (u8_t*)"|");
            i+=5;
            _delay_ms(500);

            for ( loopV2 = 0; loopV2 < counter1; loopV2++)
            {
                hglcd_displayString(pageU, i, (u8_t*)"_");
                i+=5;
                _delay_ms(500);
            }

            hglcd_displayString(pageM1, i, (u8_t*)"|");
            hglcd_displayString(pageM2, i, (u8_t*)"|");
            i+=5;
            _delay_ms(500);
            
        }
        
    }

    return 0;
}