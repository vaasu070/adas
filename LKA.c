/*
 */


#include"LKA_ADC_module.h"
#include <avr/io.h>
#include"LKA_servo.h"
#include"util/delay.h"
#include"LKA.h"



int LKA_ON(void)
{



float cm1, cm2, speed;
int yaw_angle;




LKA_servo_init();
LKA_InitADC();



CLR_BIT(DDRD,PD0);
CLR_BIT(DDRD,PD3);
SET_BIT(PORTD,PD0);
SET_BIT(PORTD,PD3);


SET_BIT(DDRD,PD7);



    while(1)
    {





if(!READ_BIT(PIND,PD0))
     {


       cm1=(LKA_ReadADC(0)*160.0)/1023.0;



         cm2=(LKA_ReadADC(1)*160.0)/1023.0;


        yaw_angle=(30.0*LKA_ReadADC(2))/512.0 - 30;


         speed=(LKA_ReadADC(3))*170/1023.0;




 if(READ_BIT(PIND , PD3)){


    if(cm1 < 30&& cm2<30 && speed > 30 && speed <= 80 && yaw_angle!= 0 )
         {



correction(yaw_angle);
         }
    else if(cm1  < 50 && cm2 < 50 && speed > 80 && speed<=150 && yaw_angle!=0){

            correction(yaw_angle);
         }else if(cm1 < 30 && cm2 > 30 && speed > 30 && speed<=80 && yaw_angle<0){
            correction(yaw_angle);
         }
        else if(cm1 < 50 && cm2 > 50 && speed > 80 && speed<=150 && yaw_angle<0){
            correction(yaw_angle);
         }

         else if(cm1 > 30 && cm2 < 30 && speed > 30 && speed<=80 && yaw_angle>0){
            correction(yaw_angle);
         }
         else if(cm1 > 50 && cm2 < 50 && speed > 80 && speed<=150 && yaw_angle>0){
            correction(yaw_angle);
         } else

         {
         LKA_servo(90);

         }
 }
else{

          LKA_servo(90);



}
    }

else
       {
           LKA_servo(90);




       }
}
  return 0;
}



void correction(int yaw_angle)
{

SET_BIT(PORTD,PD7);
_delay_ms(500);
CLR_BIT(PORTD,PD7);

LKA_servo(90+yaw_angle);
_delay_ms(2000);
LKA_servo(90);
_delay_ms(1000);

}



