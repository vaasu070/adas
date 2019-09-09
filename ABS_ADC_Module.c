/******************************************************************************
*                      Includes
******************************************************************************/
#include <avr/io.h>
#include "ABS_ADC_Module.h"
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
void ABS_ADC_initialize()
{
    ADMUX |= (1<<REFS0);                                    // Select Vref=AVcc
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);   //set pre scaller to 128 and enable ADC
}
int16_t ABS_READ_ADC(int8_t ADCchannel)
{
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);           //select ADC channel with safety mask
    ADCSRA |= (1<<ADSC);                                     //single conversion mode
    while( ADCSRA & (1<<ADSC) );                            // wait until ADC conversion is complete
    return ADC;
}
/******************************************************************************
*                      Internal functions
******************************************************************************/


/******************************************************************************
*                      End of File
******************************************************************************/
