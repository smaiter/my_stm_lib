#include "../inc/rcc.h"
/*------------------------------------------------------------*/
void rcc_cr(enum rcc_cr_reg reg, char value) 
{
  switch (reg) 
  {
    case PLLON: case CSSON: case HSEBYP: case HSEON: case HSION:
      RCC_CR = (RCC_CR & ~(1<<reg)) | (value << reg);
      break;

    case HSITRIM:
      RCC_CR = (RCC_CR & ~(0b11111<<reg)) | (value << reg);
      break;
   
    case PLLRDY: case HSERDY: case HSIRDY: case HSICAL:
      //---dummy---
      break;
  }
  return;
}

char rcc_cr_state(enum rcc_cr_reg reg)
{
  switch (reg)
  {
    case PLLRDY: case HSERDY: case HSIRDY:
      return ((RCC_CR & (1<<reg))>>reg);
      break;

    case PLLON: case CSSON: case HSEBYP: case HSEON: case HSION:
      return ((RCC_CR & (1<<reg))>>reg);
      break;
      
    case HSICAL:
      return ((RCC_CR & (0b11111111<<reg))>>reg);
      break;

    case HSITRIM:
      return ((RCC_CR & (0b11111<<reg))>>reg);
      break;
  }
  return 0;
}

void rcc_cfgr(enum rcc_cfgr_reg reg, char value)
{
  switch (reg)
  {
    case PLLMUL: case HPRE:
      RCC_CFGR = (RCC_CFGR & ~(0b1111<<reg)) | (value << reg);
      break;

    case PLLXTPRE: case PLLSRC:
      RCC_CFGR = (RCC_CFGR & ~(1<<reg)) | (value << reg);
      break;

    case ADCPRE: case SW:
      RCC_CFGR = (RCC_CFGR & ~(0b11<<reg)) | (value << reg);
      break;

    case PPRE1: case PPRE2:
      RCC_CFGR = (RCC_CFGR & ~(0b111<<reg)) | (value << reg);
      break;

    case SWS:
      break;
  }
}

char rcc_cfgr_state(enum rcc_cfgr_reg reg)
{
  switch (reg)
  {
 
    case PLLMUL: case HPRE:
      return ((RCC_CFGR & (0b1111<<reg))>>reg);
      break;

    case PLLXTPRE: case PLLSRC:
      return ((RCC_CFGR & (1<<reg))>>reg);
      break;

    case ADCPRE: case SW: case SWS:
      return ((RCC_CFGR & (0b11<<reg))>>reg);
      break;

    case PPRE1: case PPRE2:
      return ((RCC_CFGR & (0b111<<reg))>>reg);
      break;
  }
return 0;
}

