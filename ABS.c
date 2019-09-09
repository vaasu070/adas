/**********************************************************************************
Created by : SOUGAT KUMAR SARANGI(141670), Batch 1907PESMBB01
Date& Time: 08/08/2019, 5:00 PM
***********************************************************************************
Problem statement - Anti-Lock Braking System
***********************************************************************************
HARDWARE CONNECTIONS IN SIMULIDE

- Engine Switch                 -> PD3
- BRAKE Switch                  -> PD4
- Velocity Sensor(Potentiometer)-> PC0
- Angular Velocity Sensor(-do-) -> PC1
- PWM Output (CRO)              -> PD6
- LED for Full Slip             -> PD2
- LED for Partial Slip          -> PD1
- LED for No Slip               -> PD0
*************************************************************************************
DESCRIPTION FOR THE FIRMWARE

1. Press Engine Switch
2. Set the brakes.
3. If brake is applied:
    3.1. Timer0 Starts and count upto 1sec using TIMER0_OVF_vect in the main program.
            (The delay has been provided to prevent sudden switching of modes due to
             changes that are for a very short while)
    3.2. After 1sec the flag(FLAG) will generate and after the flag generates the ADC
    3.3. Reads the ADC value and accordingly the PWM generates.
4. Files Attached are :
      - Timer_Module.c
      - Timer_Module.h
      - PWM_Module.c
      - PWM_Module.h
      - ADC_Module.c
      - ADC_Module.h
      - LCD.c
      - LCD.h
****************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ABS_ADC_Module.h"

#include "ABS_PWM_Module.h"
#include"ABS.h"
/*--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------*/


int ABS_ON()
{



    CLR_BIT(DDRD,Engine_Switch);        /* making PD3 as Input - ENGINE SWITCH */
    SET_BIT(PORTD,Engine_Switch);       /* PULL UP Enabled */
    CLR_BIT(DDRD,BRAKE_Switch);         /* making PD4 as Input - BRAKE ON/OFF */
    SET_BIT(PORTD,BRAKE_Switch);        /* PULL UP Enabled */
    SET_BIT(DDRB,LED_No_Slip);          /* making PD0 as output */
    SET_BIT(DDRB,LED_Partial_Slip);     /* making PD1 as output */
    SET_BIT(DDRB,LED_Full_Slip);        /* making PD2 as output */
    SET_BIT(DDRC,MIL_Lamp);             /* making PD2 as output */

    ABS_ADC_initialize();
    ABS_ENABLE_ADC;



    ABS_PWM_initialize();



   			                /* Initialization of LCD*/

    while(1)
    {

        if(!(READ_BIT(PIND,Engine_Switch)))              /* Checking whether the Engine switch is ON or OFF */
        {
/*--------------------------- BRAKE CONDITION ---------------------------------------*/
            if(!(READ_BIT(PIND,BRAKE_Switch)))
            {
                   float velocity     = 0;
float w_actual     = 30;
float w_required   = 0;
float wheel_radius = 0.3;   /* Wheel Radius = 0.3m (12 inch diameter) */
float slip         = 0;
int Input_ADC_value=0;


                       /* ENABLE THE TIMER INTERRUPT */

                    Input_ADC_value = ABS_READ_ADC(0);       /* Read ADC value */
                    velocity = 67*Input_ADC_value/1024;
                    Input_ADC_value = ABS_READ_ADC(1);
                    w_actual = 150*Input_ADC_value/1024;
                    w_required = velocity/wheel_radius;
                    slip = 1-(w_actual/w_required);

                    if(slip<=0.2)
                        {
                       ABS_SET_PWM_VALUE(252);
                        CLR_BIT(PORTC, MIL_Lamp);
                        CLR_BIT(PORTB, LED_Partial_Slip);
                        CLR_BIT(PORTB, LED_Full_Slip);
                        SET_BIT(PORTB, LED_No_Slip);
                        _delay_ms(500);

                        }
                    else if(slip>0.3 && slip<0.7)
                        {
                       ABS_SET_PWM_VALUE(192);
                        CLR_BIT(PORTC, MIL_Lamp);
                        CLR_BIT(PORTB, LED_No_Slip);
                        CLR_BIT(PORTB, LED_Full_Slip);
                        SET_BIT(PORTB, LED_Partial_Slip);
                        _delay_ms(500);
                    	/* Write string on 2nd line*/
                        }
                    else if(slip>0.7 && slip<=1)
                        {
                       ABS_SET_PWM_VALUE(128);
                        CLR_BIT(PORTC, MIL_Lamp);
                        CLR_BIT(PORTB, LED_No_Slip);
                        CLR_BIT(PORTB, LED_Partial_Slip);
                        SET_BIT(PORTB, LED_Full_Slip);
                        _delay_ms(500);
                                  /* Write string on 2nd line*/
                        }
                    else
                    {
                       ABS_SET_PWM_VALUE(0);
                        CLR_BIT(PORTB, LED_No_Slip);
                        CLR_BIT(PORTB, LED_Partial_Slip);
                        CLR_BIT(PORTB, LED_Full_Slip);
                        SET_BIT(PORTC, MIL_Lamp);
                        _delay_ms(500);


                    }


            }
        }
/*--------------------------- ENGINE OFF Condition ------------------------------*/
        else
        {

           ABS_SET_PWM_VALUE(0);
        }
      }
    return 0;
}


