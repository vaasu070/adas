/******************************************************************************
* File Name: pwm.h
* Description:  Generation of PWM signals - prototype declaration
* Tool-Chain: avr-gcc
*
* Modification History:
*  Created by:      Khyathi Surendra   V1.0      7/aug/19
*  Description:     V1.0
*
******************************************************************************/

/******************************************************************************
*                      Includes
******************************************************************************/
/******************************************************************************
*                      Defines and data types
******************************************************************************/

#define SET_BIT(PORT,PIN)  PORT |= (1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT &= ~(1<<PIN)
/******************************************************************************
*                      Global variables
******************************************************************************/

/******************************************************************************
*                      Public function prototypes
******************************************************************************/
void BSM_PWM_init();
/******************************************************************************
*                      End of File
******************************************************************************/












