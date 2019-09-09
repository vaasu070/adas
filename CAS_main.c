/*
Created by : Alluri Durga Rao(141655), Meraki-1,
Date& Time: 27/7/2019,1:41 PM

Problem statement - Collision Avoidance System

Hardware connections of SimuleIDE
- Engine Switch -> PD0
- Speed Control-> PC1
- Ultra Sonic Sensor(Potentiometer) -> PC0
- RADAR Sensor-> PC2
- Warning Light(LED)->PD1
- Warning Buzzer->PD2
- Automatic Brakes->PD3
- ManualBraking->PD4


Description of Firmware :

1. Press Engine Switch
2. Reads the ADC value from the Speed Sensor.
3. If the Speed is greater than 20km/hr RADAR Sensor operates the LED,Buzzer and applies brakes according to the variation of the distance.
4.If the speed is between 20km/hr to 50km/hr Radar Sensor operates
 Corresponding Distances
   R>40:No Warning system and Auto braking
   35m<R<40m: Warning Light(LED) will operate.
   30m<R<35m: Both Warning Light(LED) and Buzzer will operate
   R<30m:     LED,Buzzer and automatic braking will apply
5.If the speed is between 50km/hr to 100km/hr Radar Sensor operates
 Corresponding Distances
   R>50:No Warning system and Auto braking
   45m<R<50m: Warning Light(LED) will operate.
   40m<R<45m: Both Warning Light(LED) and Buzzer will operate
   R<40m:     LED,Buzzer and automatic braking will apply
6.If the speed is between 50km/hr to 100km/hr Radar Sensor operates
 Corresponding Distances
   R>600:No Warning system and Auto braking
   55m<R<60m: Warning Light(LED) will operate.
   50m<R<55m: Both Warning Light(LED) and Buzzer will operate
   R<50m:     LED,Buzzer and automatic braking will apply
7. If the Speed from Speed is less than 50km/hr UltraSonic  Sensor operates the LED,Buzzer and applies brakes according to the variation of the distance.
  Distances for ULTRA SONIC SENSOR Sensor:
   6m<R<4m:    Warning Light(LED) will operate.
   4m<R<3m: Both Warning Light(LED) and Buzzer will operate
   R<3m:       LED,Buzzer and automatic braking will apply
8. In both sensor when we apply manual braking after LED, Buzzer warnings will OFF
9. Files Attached are :
      - adc.c
      - adc.h
      -speed.c
      -speed.h

*/

#include <avr/io.h>
#include<stdint.h>
#include"CAS_adc.h"
#include"CAS_speed.h"
#include<util/delay.h>
#define SET_BIT(PORT,BIT) PORT|= (1<<BIT)
#define CLR_BIT(PORT,PIN) PORT&=~(1<<PIN)
#define READ_BIT(PORT,PIN) PORT&(1<<PIN)

int CAS_ON(void)
{

    // Insert code
   CLR_BIT(DDRD,PD0); //Engine INPUT
   SET_BIT(PORTD,PD0); //Pull UP high configuration

   CLR_BIT(DDRD,PD1);
   SET_BIT(PORTD,PD1);

   SET_BIT(DDRB,PB3); //PD1 as Output
   SET_BIT(DDRB,PB4); //PD2 as Output
   SET_BIT(DDRB,PB5); //PD3 as Output

    CAS_InitADC();



    while (1){

if(!(PIND&(1<<PD0)))
{


 // Switching ON the RADAR Sensor when Speed is greater than 50 km/hr
        if(speed_val(1)>=20)// Corresponding potentiometer value in hardware is 0.67V
            {
                   if(speed_val(1)<=50)// Corresponding potentiometer value in hardware is 1.67V
                   {
                    // Turn on the Warning Light when distance is between 40 meters to 35 meters
                if(CAS_ReadADC(0x02)>=359 && CAS_ReadADC(0x02)<410)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                   SET_BIT(PORTB,PB3);
                   CLR_BIT(PORTB,PB4);
                   CLR_BIT(PORTB,PB5);
                }
       // Turn on the Warning Light and Buzzer when Distance is between 35 meters to 30 meters
                  else if(CAS_ReadADC(0x02)>=308 && CAS_ReadADC(0x02)<359)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                         CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                     SET_BIT(PORTB,PB4);
                     CLR_BIT(PORTB,PB5);
                }
      // Turn on the  Automatic Braking, Warning Light and Buzzer when Distance is less than 10 meters
                 else if (CAS_ReadADC(0x02)<308)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                     SET_BIT(PORTB,PB4);
                     SET_BIT(PORTB,PB5);
                }
      //Turn OFF mode when distance is greater than 40 meters
                else if((CAS_ReadADC(0x02))>=410&&(CAS_ReadADC(0x02))==0)
                {
                    CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
                   }
                if(speed_val(1)>50&&speed_val(1)<=100)// Corresponding potentiometer value in hardware is 1.64-3.34V
                    {
                    // Turn on the Warning Light when distance is between 50 meters to 45 meters
                if(CAS_ReadADC(0x02)>=461 && CAS_ReadADC(0x02)<512)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
       // Turn on the Warning Light and Buzzer when Distance is between 45 meters to 40 meters
                  else if(CAS_ReadADC(0x02)>=410 && CAS_ReadADC(0x02)<461)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                        SET_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
      // Turn on the  Automatic Braking, Warning Light and Buzzer when Distance is less than 40 meters
                 else if (CAS_ReadADC(0x02)<410)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                         CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                       SET_BIT(PORTB,PB4);
                        SET_BIT(PORTB,PB5);

                }
      //Turn OFF mode when distance is greater than 50 meters
                else if((CAS_ReadADC(0x02))>=512&&(CAS_ReadADC(0x02))==0)
                {
                    CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
                   }
            if(speed_val(1)>100&&speed_val(1)<=150)// Corresponding potentiometer value in hardware is 3.34-5.0V
                {
                    // Turn on the Warning Light when distance is between 60 meters to 55 meters
                if(CAS_ReadADC(0x02)>=564 && CAS_ReadADC(0x02)<615)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                   SET_BIT(PORTB,PB3);
                   CLR_BIT(PORTB,PB4);
                   CLR_BIT(PORTB,PB5);
                }
       // Turn on the Warning Light and Buzzer when Distance is between 55 meters to 50 meters
                  else if(CAS_ReadADC(0x02)>=512 && CAS_ReadADC(0x02)<564)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                       CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB1);
                     SET_BIT(PORTB,PB2);
                     CLR_BIT(PORTB,PB3);
                }
      // Turn on the  Automatic Braking, Warning Light and Buzzer when Distance is less than 50 meters
                 else if (CAS_ReadADC(0x02)<512)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                       SET_BIT(PORTB,PB4);
                        SET_BIT(PORTB,PB5);
                }
      //Turn OFF mode when distance is greater than 60 meters
                else if((CAS_ReadADC(0x02))>=615&&(CAS_ReadADC(0x02))==0)
                {
                   CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
                   }
        }
        // Switching ON the ULTRA SONIC sensor when speed is less than 50km/hr
            else if(speed_val(1)<20) // Corresponding potentiometer value in hardware is 0.67V
            {
        // Turn on the Warning Light when distance is between 6 meters to 4 meters
                 if(CAS_ReadADC(0x00)>=684 && CAS_ReadADC(0x00)<1000)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                        CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                   SET_BIT(PORTB,PB3);
                       CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
       // Turn on the Warning Light and Buzzer when Distance is between 4 meters to 3 meters
                else if(CAS_ReadADC(0x00)>=512 && CAS_ReadADC(0x00)<684 )
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual Braking
                    {
                       CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                       SET_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }
      // Turn on the  Automatic Braking, Warning Light and Buzzer when Distance is less than 3 meters
                 else if (CAS_ReadADC(0x00)<512)
                    if(!(READ_BIT(PIND,PD1))) //Applying Manual braking
                    {
                       CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                    }
                    else
                {
                     SET_BIT(PORTB,PB3);
                       SET_BIT(PORTB,PB4);
                        SET_BIT(PORTB,PB5);
                }
      //Turn OFF mode when distance is greater than 6 meters
                else if(CAS_ReadADC(0x00)>=1000)
                {
                   CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
                }

        }
    } else{
                       CLR_BIT(PORTB,PB3);
                        CLR_BIT(PORTB,PB4);
                        CLR_BIT(PORTB,PB5);
    }

    }

    return 0;
}
