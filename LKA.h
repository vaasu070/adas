
#define SET_BIT(PORT,PIN) PORT|=(1<<PIN)
#define CLR_BIT(PORT,PIN) PORT&=!(1<<PIN)
#define READ_BIT(PORT, PIN) (PORT&(1<<PIN))


extern int LKA_ON(void);
//static void correction(int);
