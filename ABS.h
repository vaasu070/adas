
#define SET_BIT(PORT,PIN)  PORT |= (1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT &= ~(1<<PIN)
#define READ_BIT(PORT,PIN) PORT & (1<<PIN)

#define Engine_Switch       PD0
#define BRAKE_Switch        PD1
#define LED_Full_Slip       PB5
#define LED_Partial_Slip    PB4
#define LED_No_Slip         PB3
#define MIL_Lamp            PC6

extern int ABS_ON(void);
