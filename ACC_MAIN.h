

#define INTERRUPT_INIT  SREG |= (1<<7) // GLOBAL interrupt enabled

#define SET_BIT(PORT,PIN)  PORT |= (1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT &= ~(1<<PIN)
#define READ_BIT(PORT,PIN) PORT & (1<<PIN)





extern int ACC_ON(void);
