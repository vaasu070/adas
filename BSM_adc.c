
/******************************************************************************
* File Name: adc.c
* Description:  Analog to digital conversion
* Tool-Chain: avr-gcc
*
*  Modification History:
*  Created by: Khyathi Surendra   V1.0      08/Aug/19
*  Description:     V1.0
******************************************************************************/

/******************************************************************************
*                      Includes
******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BSM_adc.h"
/******************************************************************************
*                      Defines and data types
******************************************************************************/

/******************************************************************************
*                      Global variables
******************************************************************************/

/******************************************************************************
*                      Static variables
******************************************************************************/


/******************************************************************************
*                      Internal function prototypes
******************************************************************************/

// code

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

// code

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
uint16_t BSM_READ_ADC()
{
    CLR_BIT(DDRC,PC0);
    ADMUX  |= (1<<REFS0);
    ADCSRA |= (1 << ADSC);
    ADCSRA |= ((1<<ADPS1)|(1<<ADPS2)); // 64 pre scaler
    while (ADCSRA & (1 << ADSC));
return ADC;
}

/******************************************************************************
*                      End of File
******************************************************************************/


