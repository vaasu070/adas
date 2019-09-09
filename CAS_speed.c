/******************************************************************************
* File Name: speed.c
* Description:  This file contains functions of selecting different speeds program
* Tool-Chain: IAR Systems iccrl78
*
*  Modification History:
*  Created by:     Alluri Durga Rao    V1.0      08/Aug/19
*  Description:     V1.0
******************************************************************************/

/******************************************************************************
*                      Includes
******************************************************************************/
#include"CAS_speed.h"
#include"CAS_adc.h"
/******************************************************************************
*                      Public functions
******************************************************************************/
/******************************************************************************
* Name:speed_val (void)
* Description:  Converts the Analog value from Potentiometer to the digital value

* Arguments: pin
* Returns:speed_value
******************************************************************************/

 uint16_t speed_val(uint16_t pin)
 {
       uint16_t speed_value=((CAS_ReadADC(pin))*150.0)/1023;
       return speed_value;
 }

