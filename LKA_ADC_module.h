/******************************************************************************
* File Name: LKA_ADC_module.h
* Description:  This file contains function Prototypes of ADC module
* Tool-Chain: AVR
*
* Modification History:
*  Created by: Sankeerth Potelu
*
******************************************************************************/

#ifndef LKA_ADC_module_H
#define LKA_ADC_module_H
/******************************************************************************
*                      Includes
******************************************************************************/

#include<avr/io.h>
//#include<util/delay.h>
#include<avr/interrupt.h>

//#define DISABLE_ADC() ADCSRA&= ~(1<<ADEN);
//#define ENABLE_ADC()  ADCSRA| = (1<<ADEN);
/*******************************************************************
            Public function prototypes
********************************************************************/

//* Name: Init_ADC(void)
//* Description:  Intializes the ADC
extern void LKA_InitADC();

//* Name: Read_ADC(void)
//* Description:  Read the ADC databn
extern uint16_t ReadADC(uint8_t ADCchannel);


/******************************************************************************
*                      End of File
******************************************************************************/
#endif

