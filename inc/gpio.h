//General-purpose and alternate-function I/Os (GPIOs and AFIOS), RM0008 9-159
//author: alexand_dm, Keil
//version: 0.1: created 28.01.18
//version: 0.2: 06.02.18, insert structure from stm32f10x.h

#define GPIOA_BASE            0x40010800
#define GPIOB_BASE            0x40010C00
#define GPIOC_BASE            0x40011000
#define GPIOD_BASE            0x40011400
#define GPIOE_BASE            0x40011800
#define GPIOF_BASE            0x40011C00
#define GPIOG_BASE            0x40012000
/*-------------------------GPIOC registers-------------------------*/
#define GPIOC_CRL             *(volatile int*)(GPIOC_BASE+0x00)
#define GPIOC_CRH             *(volatile int*)(GPIOC_BASE+0x04)
#define GPIOC_ODR             *(volatile int*)(GPIOC_BASE+0x0c)
#define GPIOC_BSRR            *(volatile int*)(GPIOC_BASE+0x10)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)

/*-------------------------GPIOB_CRL_bit_def-------------------------*/
#define CN7_MODE7_bit       28
#define CN6_MODE6_bit       24
#define CN7_MODE7(value)    ((GPIOB->CRL & ~(0b1111<<CN7_MODE7_bit)) | (value<<CN7_MODE7_bit))
#define CN6_MODE6(value)    ((GPIOB->CRL & ~(0b1111<<CN6_MODE6_bit)) | (value<<CN6_MODE6_bit))

typedef struct
{
volatile unsigned long CRL;
volatile unsigned long CRH;
volatile unsigned long IDR;
volatile unsigned long ODR;
volatile unsigned long BSRR;
volatile unsigned long BRR;
volatile unsigned long LCKR;
} GPIO_TypeDef;
/*-------------------------Function prototype-------------------------*/

enum gpioc_crl_reg
{
  CNF7  =30,
  MODE7 =28,
  CNF6  =26,
  MODE6 =24,
  CNF5  =22,
  MODE5 =20,
  CNF4  =18,
  MODE4 =16,
  CNF3  =14,
  MODE3 =12,
  CNF2  =10,
  MODE2 =8,
  CNF1  =6,
  MODE1 =4,
  CNF0  =2,
  MODE0 =0,
};

enum gpioc_crh_reg
{
  CNF15  =30,
  MODE15 =28,
  CNF14  =26,
  MODE14 =24,
  CNF13  =22,
  MODE13 =20,
  CNF12  =18,
  MODE12 =16,
  CNF11  =14,
  MODE11 =12,
  CNF10  =10,
  MODE10 =8,
  CNF9   =6,
  MODE9  =4,
  CNF8   =2,
  MODE8  =0,
};

enum gpioc_odr_reg
{
  ODR15 =15,
  ODR14 =14,
  ODR13 =13,
  ODR12 =12,
  ODR11 =11,
  ODR10 =10,
  ODR9  =9,
  ODR8  =8,
  ODR7  =7,
  ODR6  =6,
  ODR5  =5,
  ODR4  =4,
  ODR3  =3,
  ODR2  =2,
  ODR1  =1,
  ODR0  =0,
};

void gpioc_crl(enum gpioc_crl_reg reg, char value);
void gpioc_crh(enum gpioc_crh_reg reg, char value);
void gpioc_odr(enum gpioc_odr_reg reg, char value);
