//Inter-integrated circuit (I2C) interface, stm32f103c8t6 header file, RM0008 26-743
//author: alexand_dm, Keil
//version: 0.1: created 2018-02-28


#define I2C1_BASE             0x40005400
#define I2C2_BASE             0x40005800

#define I2C1                  ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                  ((I2C_TypeDef *) I2C2_BASE)



/*--------------------I2C_CR1--------------------*/
#define STOP                  (uint16_t)(0x0200)
#define START                 (uint16_t)(0x0100)
#define PE                    (uint16_t)(0x0001)

/*--------------------I2C_CR2--------------------*/
#define FREQ_adr              0
#define FREQ(value)           (value<<FREQ_adr)
  
/*--------------------I2C_CCR--------------------*/
#define CCR_bit_mask          (0x0fff)
#define CCR_adr               0
#define CCR(value)            (value<<CCR_adr)

/*--------------------I2C_TRISE--------------------*/

typedef struct
{
  uint16_t CR1;
  uint16_t  RESERVED0;
  uint16_t CR2;
  uint16_t  RESERVED1;
  uint16_t OAR1;
  uint16_t  RESERVED2;
  uint16_t OAR2;
  uint16_t  RESERVED3;
  uint16_t DR;
  uint16_t  RESERVED4;
  uint16_t SR1;
  uint16_t  RESERVED5;
  uint16_t SR2;
  uint16_t  RESERVED6;
  uint16_t CCR;
  uint16_t  RESERVED7;
  uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;


/*--------------------Functions prototypes--------------------*/
void i2c1_start();
void i2c1_stop();
void i2c1_slave_adr(uint16_t s_adr);
