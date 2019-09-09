#include <avr/io.h>

#define OUTPUT(PORT,PIN) PORT|=(1<<PIN)
#define INPUT(PORT,PIN) PORT&=~(1<<PIN)
#define READ(PORT,PIN) !(PORT&(1<<PIN))
#define PULL_HIGH(PORT,PIN) PORT|=(1<<PIN)

static void conf(void);
extern int isBack(void);
