//SysTick timer (STK), PM0056 Rev5, 4-150 
//file:systick.c
//author: alexand_dm
//version: 0.1: created 30.01.18
//version: 0.2: 13.02.18, add delay(us) function
#include "../inc/systick.h"

void stk_delayUS(int delay)
{
  STK->LOAD=(AHB_clock*delay);
  STK->CTRL=0x5; //systick count enable, clksource AHB

  while ((STK->CTRL & 0x10000)==0); //wait stk ctrl countflag=1
  
  STK->CTRL=0;
  STK->VAL=0;
}
