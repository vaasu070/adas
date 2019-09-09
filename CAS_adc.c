/******************************************************************************
* File Name: adc.c
* Description:  This file contains functions of analog to digital conversion program
* Tool-Chain: IAR Systems iccrl78
*
*  Modification History:
*  Created by:      Alluri Durga Rao    V1.0      08/Aug/19
*  Description:     V1.0
******************************************************************************/

/******************************************************************************
*                      Includes
******************************************************************************/
#include"CAS_adc.h"
/******************************************************************************
*                      Public functions
******************************************************************************/
/******************************************************************************
* Name:InitADC(void)
* Arguments: None
* Returns:None
******************************************************************************/

void CAS_InitADC()
{
 // Select Vref=AVcc
 ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC
 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}
/******************************************************************************
*                      Public functions
******************************************************************************/
/******************************************************************************
* Name:READADC (void)
* Description:  Reads the ADC value of the particular channel
* Arguments: ADC Channel
* Returns:ADC
******************************************************************************/


uint16_t CAS_ReadADC(uint16_t ADCchannel)
{
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 return ADC;
}
