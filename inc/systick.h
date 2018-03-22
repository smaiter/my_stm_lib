//author: alexand_dm, keil
//version: 0.1: created 30.01.18
//version: 0.2: 12.02.18, insert structure from stm32f10x.h

#define SysTick_BASE             (0xE000E010)
/*-------------------------SysTick registers-------------------------*/
#define STK             ((SysTick_TypeDef *)SysTick_BASE)     

#define AHB_clock       32        //Mhz 

typedef struct
{
  volatile unsigned long CTRL;              
  volatile unsigned long LOAD;            
  volatile unsigned long VAL;        
  volatile unsigned long CALIB;     
} SysTick_TypeDef;

/*--------------------Functions prototype--------------------*/

enum stk_ctrl_reg
{
  COUNTFLAG =16,
  CLKSOURCE =2,
  TICKINT   =1,
  ENABLE    =0
};

enum stk_load_reg
{
  RELOAD =0
};

enum stk_val_reg
{
  CURRENT =0
};

void stk_ctrl(enum stk_ctrl_reg reg, char value);
char stk_ctrl_state(enum stk_ctrl_reg reg);
void stk_load(enum stk_load_reg reg, int value);
void stk_delayms(int delayms);
void stk_delayUS(int delay);
