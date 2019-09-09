
#include <avr/io.h>

/******************************************************************************
*                       Defines and data types
******************************************************************************/
#define SET_BIT(PORT,PIN)  PORT|=(1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT&=~(1<<PIN)
#define OUTPUT(PORT,PIN) PORT|=(1<<PIN)
#define INPUT(PORT,PIN) PORT&=~(1<<PIN)
#define READ(PORT,PIN) !(PORT&(1<<PIN))
#define PULL_HIGH(PORT,PIN) PORT|=(1<<PIN)
#include"AFS.h"
#include"CAS_main.h"
#include"BSM.h"
#include"ACC_MAIN.h"
#include"LKA.h"
#include"ABS.h"
#include"util/delay.h"
int main(void)
{



    while(1)

    {

INPUT(DDRC,PC5);
INPUT(DDRC,PC4);
INPUT(DDRD,PD4);

OUTPUT(DDRD,PD7);

PULL_HIGH(PORTC,PC5);
PULL_HIGH(PORTC,PC4);
PULL_HIGH(PORTD,PD4);






if(!READ(PINC,PC5) && !READ(PINC,PC4) && READ(PIND,PD4))//001
    {
CAS_ON();

} else if(!READ(PINC,PC5) && READ(PINC,PC4) && !READ(PIND,PD4))//010
{
BSM_ON();

}else if(!READ(PINC,PC5) && READ(PINC,PC4) && READ(PIND,PD4)){//011

AFS_ON();

} else if(READ(PINC,PC5) && !READ(PINC,PC4) && !READ(PIND,PD4)){//100
ACC_ON();

}else if(READ(PINC,PC5) && !READ(PINC,PC4) && READ(PIND,PD4)){ // 101

LKA_ON();

} if(READ(PINC,PC5) && READ(PINC,PC4) && !READ(PIND,PD4)){ // 110

ABS_ON();

}


}


    return 0;
}
