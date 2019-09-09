/******************************************************************************
* File Name: main.c
* Description:  This file contains blindspot monitor system algorithm
* Tool-Chain: avr-gcc
*
*  Modification History:
*  Created by:      Khyathi Surendra    V1.0      07/Aug/19
*  Description:     V1.0
******************************************************************************/

/******************************************************************************
*                      Includes
******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BSM_adc.h"
#include "BSM_timer.h"
#include "BSM_pwm.h"
#include"BSM.h"
/******************************************************************************
*                      Defines and data types
******************************************************************************/

/******************************************************************************
*                      Global variables
******************************************************************************/


u16 Timer_count_value=0;
u16 Final_value=0;

/******************************************************************************
*                      Static variables
******************************************************************************/

u8 index_value=0;


/******************************************************************************
*                      Internal function prototypes
******************************************************************************/
/*
static uint16_t Binary_Search_u16 (uint16_t X_array[], uint16_t N,uint16_t Xin);
static sint16_t Ifx_IntIpoCur_u16_s16(uint16_t Xin, uint16_t N, uint16_t X_array[], sint16_t Val_array[]);*/

/******************************************************************************
*                      Public functions
******************************************************************************/
/******************************************************************************
* Name: TCD_TemperatureType Tcd_CalcTemperature (void)
* Description:  Calculates the temperature using data from NTC in KELVIN
*  a)  Run time( typical ):  xx clock cycles
*  b)  Run time ( worst case ):  xx clock cycles
*
* Code Memory Used	: yy bytes	(ROM)
* Stack Used		: yy bytes	(RAM)
*
* Arguments: None
* Returns: TCD_TemperatureType - Temperature measured in KELVIN
******************************************************************************/

/******************************************************************************
*                      Internal functions
******************************************************************************/
/******************************************************************************
* Name: uint16_t Binary_Search_u16 (uint16_t X_array[], uint16_t N,uint16_t Xin)
* Description:  Finds the index of the given input
*  a)  Run time( typical ):  xx clock cycles
*  b)  Run time ( worst case ):  xx clock cycles
*
* Code Memory Used	: yy bytes	(ROM)
* Stack Used		: yy bytes	(RAM)
******************************************************************************/
/*
static uint16_t Binary_Search_u16 (uint16_t X_array[], uint16_t N,uint16_t Xin)
{
    uint16_t Min_Index;
	uint16_t Max_Index;
    uint16_t Mid_Index;

    Min_Index = 0u;
    Max_Index = N;

    while(Min_Index < Max_Index)
    {
        Mid_Index = (Min_Index + Max_Index) >> 1u;
        if (Xin > X_array[Mid_Index])
        {
            Min_Index = Mid_Index + 1u;
        }
        else
        {
            Max_Index = Mid_Index;
        }
    }
    return Min_Index;
}
*/
/******************************************************************************
* Name: Ifx_IntIpoCur_u16_s16(	uint16_t Xin,
*								uint16_t N,
*								uint16_t X_array[],
*								sint16_t Val_array[])
* Description:  interpolation library for calculating the temperature
*  a)  Run time( typical ):  xx clock cycles
*  b)  Run time ( worst case ):  xx clock cycles
*
* Code Memory Used	: yy bytes	(ROM)
* Stack Used		: yy bytes	(RAM)
******************************************************************************/


int BSM_ON()
{
CLR_BIT(DDRB,PB0);
SET_BIT(PORTB,PB0);



    u16 (*adc_ptr)() = BSM_READ_ADC;
    CLR_BIT(DDRD,PD0);   // making PD2 as Input for engine
    SET_BIT(PORTD,PD0);  //PULL UP Enabled

    CLR_BIT(DDRD,PD1);
    SET_BIT(PORTD,PD1);

    SET_BIT(DDRB,LED1_PIN);
    SET_BIT(DDRB,LED2_PIN);
    SET_BIT(DDRB,LED3_PIN);
    ADCSRA |= (1<< ADEN);

    DDRD |= (1<<PD6); // output port setter

    BSM_TIMER_init();
    BSM_PWM_init();


    SREG |= (1<<7);
    sei();



    while(1)         // Super Loop
    {

if(!(PINB & 1<<PB0)){
BSM_setDefault();
        return 0;
       }


        if(!(PIND & 1<<PD0))  // when engine is on
        {



           if(!(PIND & 1<<PD1)) // if(!(PIND & 1<<PD3))
{
 //SET_BIT(PORTD,PD7);
                        Final_value = adc_ptr();
                        if(Final_value>680)
                            {
                            OCR0A = 63; //25%
                            SET_BIT(PORTB,LED1_PIN);
                            CLR_BIT(PORTB,LED2_PIN);
                            CLR_BIT(PORTB,LED3_PIN);

                            }
                        else if(Final_value>= 341 && Final_value <=680)
                            {
                                OCR0A = 127;//50%
                            SET_BIT(PORTB,LED2_PIN);
                            CLR_BIT(PORTB,LED1_PIN);
                            CLR_BIT(PORTB,LED3_PIN);
                            }
                        else if(Final_value < 341)
                            {OCR0A = 193;//75%
                            SET_BIT(PORTB,LED3_PIN);
                            CLR_BIT(PORTB,LED1_PIN);
                            CLR_BIT(PORTB,LED2_PIN);}
                        index_value=0;
                    }
                    }


        else
        {
            TIMSK0 &= ~(1<<TOIE0); BSM_TIMER_init();
    BSM_PWM_init();

            OCR0A = 0;
        }

      }

    return 0;
}

void  BSM_setDefault(){
 OCR0A = 0;
CLR_BIT(PORTB,LED1_PIN);
CLR_BIT(PORTB,LED2_PIN);
CLR_BIT(PORTB,LED3_PIN);
}


/******************************************************************************
*                      End of File
******************************************************************************/
