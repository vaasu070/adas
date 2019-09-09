
#include<avr/io.h>
#include"util/delay.h"

void LKA_servo_init(){
TCCR1A|=(1<<WGM10);
TCCR1A&=~(1<<WGM11);
TCCR1B|=(1<<WGM12);
TCCR1B&=~(1<<WGM13);
TCCR1B|=((1<<CS12)|(1<<CS10));
TCCR1B&=~(1<<CS11);
TCNT1H=0x00;
TCNT1L=0x00;


TCCR1A|=(1<<COM1A1);
TCCR1A&=~(1<<COM1A0);
DDRB|=(1<<PB1);



}

void LKA_servo(int degrees){

int temp = ((7.8*degrees)/90);
OCR1A=temp + 15;
_delay_ms(100);

}

