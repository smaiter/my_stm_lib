#include <stdio.h>
//Medium-density reset and clock control (RCC), stm32f103c8t6 header file, RM0008 7-90.
//author: alexand_dm, Keil
//version: 0.1: created 2018.01.28
//version: 0.2: 2018-02-28 insert structure from stm32f10x.h (CMSIS)

#define RCC_BASE                  (0x40021000)

#define RCC                       ((RCC_TypeDef *) RCC_BASE)

/*--------------------RCC_CFGR bit def--------------------*/
#define PPRE1_adr                 8
#define HPRE_adr                  4 
#define PPRE1_DIV1                ((RCC->CFGR & ~(0b111<<PPRE1_adr)) | (0 << PPRE1_adr))           //HCLK not divided
#define HPRE_DIV1                 ((RCC->CFGR & ~(0b1111<<HPRE_adr)) | (0 << HPRE_adr))            //SYSCLK not divided

/*--------------------RCC_APB1ENR bit def--------------------*/
#define I2C1EN_adr                21
#define I2C1EN                    ((RCC->APB1ENR & ~(0b1<<I2C1EN_adr)) | (1<<I2C1EN_adr))

/*--------------------RCC_APB2ENR bit def--------------------*/
#define IOPCEN                    0x00000010
#define IOPBEN                    0x00000008 

/*--------------------RCC registers--------------------*/
#define RCC_CR            *(volatile uint32_t*)(RCC_BASE+0x00)
#define RCC_CFGR          *(volatile uint32_t*)(RCC_BASE+0x04)
#define RCC_APB2ENR       *(volatile uint32_t*)(RCC_BASE+0x18)

typedef struct
{
  uint32_t CR;
  uint32_t CFGR;
  uint32_t CIR;
  uint32_t APB2RSTR;
  uint32_t APB1RSTR;
  uint32_t AHBENR;
  uint32_t APB2ENR;
  uint32_t APB1ENR;
  uint32_t BDCR;
  uint32_t CSR;
} RCC_TypeDef;
/*--------------------Functions prototype--------------------*/

enum rcc_cr_reg 
{
  PLLRDY  =25, 
  PLLON   =24, 
  CSSON   =19, 
  HSEBYP  =18, 
  HSERDY  =17, 
  HSEON   =16, 
  HSICAL  =8, 
  HSITRIM =3, 
  HSIRDY  =1, 
  HSION   =0 
};

enum rcc_cfgr_reg
{
  PLLMUL   =18,
  PLLXTPRE  =17,
  PLLSRC    =16,
  ADCPRE    =14,
  PPRE2     =11,
  PPRE1     =8,
  HPRE      =4,
  SWS       =2,
  SW        =0
};


void rcc_cr(enum rcc_cr_reg reg, char value);
char rcc_cr_state(enum rcc_cr_reg);
void rcc_cfgr(enum rcc_cfgr_reg reg, char value);
char rcc_cfgr_state(enum rcc_cfgr_reg reg);
