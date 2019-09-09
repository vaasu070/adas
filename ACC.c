#include "ACC.h"
#include <avr/io.h>
#include "ACC_PWM_module.h"
#include "ACC_ADC_module.h"
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>

void ACC(float  dis,float  fv_Spd,float  ego_Spd){

 SET_BIT(DDRB,PB4);
 float  safe_dist=40.0;
 int8_t max_acclr=5,decc_Limit=-4;


    double temp1;
    double temp2;
    double temp;
    int8_t acclr=0;

    if(dis<safe_dist){

if(fv_Spd==0){
           SET_BIT(PORTB, PB4);
            temp=-ceil((ego_Spd*ego_Spd)/(2.0*dis));
            acclr=(int8_t)(temp);
}
        else

        if(fv_Spd>ego_Spd){
CLR_BIT(PORTB, PB4);
           temp1=(fv_Spd-ego_Spd);
           temp2=(safe_dist-dis);
           temp=floor(temp1*temp1/(2*temp2));
           acclr=(int8_t)(temp);
        }
        else if(fv_Spd<=ego_Spd){
CLR_BIT(PORTB, PB4);
            temp1=safe_dist/fv_Spd;
            temp2=ego_Spd*temp1;
            temp=-abs(ceil((temp2-dis)*2/(temp1*temp1)));
            acclr=(int8_t)(temp);

        }

    }
    else{

      if(fv_Spd>=ego_Spd){
             temp1=safe_dist/fv_Spd;
            temp2=ego_Spd*temp1;
            temp=abs(ceil((temp2-dis)*2/(temp1*temp1)));
            acclr=(int8_t)(temp);
        }
        else if(fv_Spd<ego_Spd){
             temp1=(fv_Spd-ego_Spd);
             temp2=(safe_dist-dis);
             temp=floor(temp1*temp1/(2*temp2));
             acclr=(int8_t)(temp);

        }

    }

    if(acclr>max_acclr)
        acclr=max_acclr;
        if(acclr<decc_Limit)
            acclr = decc_Limit;



OCR0A  = (85.0*(acclr))/3.0 + 340.0/3.0;



}

