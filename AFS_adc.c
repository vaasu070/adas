/******************************************************************************
*                      Includes
******************************************************************************/

#include"AFS_adc.h"
#include<avr/io.h>

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


/******************************************************************************
*                      Public functions
******************************************************************************/

void AFS_InitADC()
{

    // Select Vref=AVcc
    ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC
 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t AFS_ReadADC(uint8_t ADCchannel)
{

   ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);

    ADCSRA|=(1<<ADSC);
    // wait until ADC conversion is complete
    while( ADCSRA & (1<<ADSC) );
   return ADC;
}