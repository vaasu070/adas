

#define SET_BIT(PORT,PIN)  PORT |=  (1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT &= ~(1<<PIN)
#define LED1_PIN PB3
#define LED2_PIN PB4
#define LED3_PIN PB5

typedef uint16_t u16;
typedef uint8_t u8;


extern int BSM_ON(void);
