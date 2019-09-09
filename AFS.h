
#define SET_BIT(PORT,PIN)  PORT|=(1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT&=~(1<<PIN)
#define OUTPUT(PORT,PIN) PORT|=(1<<PIN)
#define INPUT(PORT,PIN) PORT&=~(1<<PIN)
#define READ(PORT,PIN) !(PORT&(1<<PIN))
#define PULL_HIGH(PORT,PIN) PORT|=(1<<PIN)


extern int AFS_ON(void);

