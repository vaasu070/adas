
#include<avr/io.h>

/******************************************************************************
*                      Includes
******************************************************************************/
#include<avr/interrupt.h>
#include<stdint.h>
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


extern void pwm_set(uint8_t pin, uint8_t dutycycle);

extern void pwm_init();