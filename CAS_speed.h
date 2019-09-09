/******************************************************************************
* File Name: speed.h
* Description:  This file contains function Prototypes of speed module
* Tool-Chain: IAR Systems iccrl78
*
* Modification History:
*  Created by:      Alluri Durga Rao    V1.0      08/Aug/19
*  Description:     V1.0
*
******************************************************************************/
#ifndef speed_H
#define speed_H


/******************************************************************************
*                      Includes
******************************************************************************/
#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdint.h>


/******************************************************************************
*                      Public function prototypes
******************************************************************************/
extern void speed_init();
extern uint16_t speed_autoval();
#endif
/******************************************************************************
*                      End of File
******************************************************************************/

