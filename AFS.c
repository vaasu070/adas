
/******************************************************************************
*                      Includes
******************************************************************************/

#include"goBack.h"
#include"AFS.h"

#include <avr/io.h>
#include <util/delay.h>
#include "AFS_servo.h"
#include <avr/interrupt.h>
#include"AFS_pwm.h"
#include"AFS_getWheelDegrees.h"

/******************************************************************************
*                       Defines and data types
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






int  AFS_ON(void)
{




    INPUT(DDRD,PD0);
    INPUT(DDRD,PD1);
    INPUT(DDRD,PD2);
    INPUT(DDRD,PD3);
    INPUT(DDRB,PB0);

    PULL_HIGH(PORTD,PD0);
    PULL_HIGH(PORTD,PD1);
    PULL_HIGH(PORTD,PD2);
    PULL_HIGH(PORTD,PD3);
    PULL_HIGH(PORTB,PB0);

    INPUT(DDRC,PC0);
    INPUT(DDRC,PC1);




    OUTPUT(DDRD,PD6);
    OUTPUT(DDRD,PD7);
    OUTPUT(DDRB,PB1);
    OUTPUT(DDRB,PB2);
AFS_InitADC();
AFS_pwm_init();



AFS_servo_init();






    while (1)
    {


       if(isBack()){
         setDefault();
        return 0;
       }

        if(READ(PIND,PD0))
        {

               float wheeldegrees = wheelDegrees();

              if(wheeldegrees>=0){

                     if(wheeldegrees>15){
                        AFS_servo_degrees(PB1,15+90);//right cone
                    AFS_servo_degrees(PB2,7.5+90); //left cone
                     }else {
                    AFS_servo_degrees(PB1,wheeldegrees+90);
                    AFS_servo_degrees(PB2,wheeldegrees/2.0 + 90);
                    }

              } else {

                  if(wheeldegrees<-15){
                        AFS_servo_degrees(PB1,-7.5+90);
                    AFS_servo_degrees(PB2,-15+90);
                     }else {
                    AFS_servo_degrees(PB1,wheeldegrees/2.0 + 90);
                    AFS_servo_degrees(PB2,wheeldegrees + 90 );
                    }

              }

            if(READ(PIND,PD1)){
                  uint16_t luminous_value = AFS_ReadADC(0);
                   AFS_pwm_set(PD6,((-100.0*luminous_value)/1023.0 )+ 100 );
                   _delay_ms(500);




            }else{

                  if(READ(PIND,PD2)){
                        AFS_pwm_set(PD6,25);
                         _delay_ms(500);

                  }else if(READ(PIND,PD3)){
                          AFS_pwm_set(PD6,75);
                           _delay_ms(500);
                  } else {
                   AFS_pwm_set(PD6,0);
                           _delay_ms(500);
                  }

            }




        }
        else
        {
            AFS_pwm_set(PD5,0);
             _delay_ms(500);
            AFS_servo_degrees(PB1, 90);
            AFS_servo_degrees(PB2, 90 );
        }

    }
}



void setDefault(){
AFS_pwm_set(PD6,0);
AFS_servo_degrees(PB1, 90);
AFS_servo_degrees(PB2, 90 );
DDRD = 0X00;
DDRC = 0X00;
DDRB = 0X00;
}

