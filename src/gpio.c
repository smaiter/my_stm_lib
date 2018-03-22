//General-purpose and alternate-function I/Os (GPIOs and AFIOS), RM0008 9-159
//file:gpio.c
//author: alexand_dm
//version: 0.1: created 28.01.18
#include "../inc/gpio.h"

void gpioc_crl(enum gpioc_crl_reg reg, char value)
{
  GPIOC_CRL = (GPIOC_CRL & ~(0b11<<reg)) | (value << reg);
}

void gpioc_crh(enum gpioc_crh_reg reg, char value)
{
  GPIOC_CRH = (GPIOC_CRH & ~(0b11<<reg)) | (value << reg);
}

void gpioc_odr(enum gpioc_odr_reg reg, char value)
{
  GPIOC_ODR = (GPIOC_ODR & ~(1<<reg)) | (value << reg);
}
