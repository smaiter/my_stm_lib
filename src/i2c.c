//Inter integrated circuit (I2C), stm32f10xx, RM0008 26-743
//author: alexand_dm,
//version: 0.1: created 2018-03-05
#include <stdint.h>
#include <i2c.h>

/*--------------------------------------------------
 *@name i2c1_start
 *@brief generate start condition to I2C1 bus
--------------------------------------------------*/
void i2c1_start()
{
  I2C1->CR1 |=START;
  while (!(I2C1->SR1 & 0x1))
  {
    asm("nop");
  }
}

/*--------------------------------------------------
 *@name i2c_slave_adr
 *@brief send to i2c1 bus slave address of device, slave_adr+0(write bit) 
 *@param[in] uint16_t s_adr (slave adr.(7 bit), include write bit 0(LSB))
--------------------------------------------------*/
void i2c1_slave_adr(uint16_t s_adr)
{
  I2C1->DR=s_adr;
  while (!(I2C1->SR1 & 0x2))
  {
    asm("nop");
  }
  
  while (!(I2C1->SR2 & 0x1))
  {
    asm("nop");
  }
}

/*--------------------------------------------------
 *@name i2c1_stop
 *@brief stop condition to i2c bus
--------------------------------------------------*/
void i2c1_stop()
{
  I2C1->CR1|=STOP;
}
