/******************************************************************************
* File Name: main.c
* Description: This file contains simulation file and embedded code for Adaptive Cruise Control.
Name : Sairanjan Rout.
ID :141667
Date of submission: 7/09/2019
Problem statement - Adaptive Cruise Control.
connections of Simule IDE
- Engine Switch -> PD2
- Set ACC switch -> PD3
- ACC ON or OFF Indicator -> PB5
- Manual Brake Pedal -> PB7
- Manual Acceleration Pedal -> PD5
- Seat belt control -> PB3
- Approaching Distance Sensor(Potentiometer) -> PC0
- Front vehicle speed (speed sensor sensor|Voltmeter) -> PC1
- Host speed sensor -> PC2
- Ossiloscope for PWM pulse display -> PD6
- Brake signal Indicator-> PB2
******************************************************************************/
/******************************************************************************
*                      Includes
******************************************************************************/


#include "ACC_ADC_module.h"

#include "ACC_PWM_module.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include"ACC_MAIN.h"

/******************************************************************************
*                      Defines and data types
******************************************************************************/




/******************************************************************************
*                            main function
******************************************************************************/


int ACC_ON()
{

float dis,fv_Spd,ego_Spd;






CLR_BIT(DDRB,PB0);
SET_BIT(PORTB,PB0);




    CLR_BIT(DDRD,PD0);
    SET_BIT(PORTD,PD0);
    CLR_BIT(DDRD,PD1);
    SET_BIT(PORTD,PD1);

    CLR_BIT(DDRB,PB7);
    SET_BIT(PORTB,PB7);
    CLR_BIT(DDRD,PD2);
    SET_BIT(PORTD,PD2);
    CLR_BIT(DDRD,PD5);
    SET_BIT(PORTD,PD5);

    SET_BIT(DDRB,PB4);


    SET_BIT(DDRB,PB5);
    CLR_BIT(PORTB,PB5);

    ACC_ADC_start();
    ENABLE_ADC;


    ACC_PWM_start();


    while(1)
    {

if(!(PINB & 1<<PB0)){
ACC_setDefault();
        return 0;
       }

      if(!(READ_BIT(PIND,PD0)))  // ENGINE ON//
        {

           if(!(READ_BIT(PIND,PD2))) //SEAT BELT ON//
            {
//******************************ACC_MODE_ON**************************************************************************************//

                if(!(READ_BIT(PIND,PD1))) // ACC ON//
                    {
                    if((READ_BIT(PIND,PD5) && READ_BIT(PINB,PB7)))
                        {

                                SET_BIT(PORTB, PB5);

                               dis = (ACC_READ_ADC(0)*200.0)/1023.0;  // Read ADC dis
                               fv_Spd=(ACC_READ_ADC(1)*40.0)/1023.0;
                               ego_Spd=(ACC_READ_ADC(2)*40.0)/1023.0;

                               ACC(dis,fv_Spd,ego_Spd);





                    }
//*******************************************ACC OFF*****************************************************************//
                    else
                        {
                            CLR_BIT(PORTB,PB5);

                             SET_PWM_VALUE(0);
                             //SET_PWM_VALUE((100.0*value2)/1023.0);


                        }
                }


            else
            {
                CLR_BIT(PORTB,PB5);

                         SET_PWM_VALUE(0);
                        //SET_PWM_VALUE((100.0*value2)/1023.0);

            }

           }
            else{
                CLR_BIT(PORTB,PB5);

                SET_PWM_VALUE(0);
            }
        }
        else{
            CLR_BIT(PORTB,PB5);

            SET_PWM_VALUE(0);
        }




    }
    return 0;
}

void ACC_setDefault(){
CLR_BIT(PORTB,PB5);
CLR_BIT(PORTB,PB4);
SET_PWM_VALUE(0);
}

/******************************************************************************
*                      End of File
******************************************************************************/


