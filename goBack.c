
#include"goBack.h"


void conf(){

INPUT(DDRB,PB0);
PULL_HIGH(PORTB,PB0);
}

int  isBack(){



return READ(PINB,PB0);
}
