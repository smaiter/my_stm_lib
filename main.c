#include <rcc.h>
#include <i2c.h>
#include <gpio.h>
#include <dwt.h>
#include <systick.h>
#include <1-wire.h>
#include <ds18b20.h>
#include <ssd1306.h>
#include <grbuf.h>

int main() {
  //RCC settings-------------------------
  rcc_cr(HSEON,1);
  while (1^rcc_cr_state(HSERDY));

  rcc_cfgr(PLLXTPRE, 0);
  rcc_cfgr(PLLSRC,1);
  rcc_cfgr(PLLMUL,0b0010); //pll multiplication factor x4
  rcc_cfgr(SW,0b10);

  rcc_cr(PLLON,1);
  while (1^rcc_cr_state(PLLRDY));

  RCC->CFGR = HPRE_DIV1;
  RCC->CFGR = PPRE1_DIV1;
  RCC->APB1ENR = I2C1EN;

  I2C1->CR2 |= FREQ(32);
  I2C1->CCR |= CCR(320);
  I2C1->TRISE = 33;  
  I2C1->CR1 |= PE;

  //RCC->APB2ENR |= IOPCEN;
  RCC->APB2ENR |= IOPBEN;

  GPIOB->CRL = CN7_MODE7(0b1110); //Altrnate function Open-drain(PB7) for I2C1
  GPIOB->CRL = CN6_MODE6(0b1110); //Altrnate function Open-drain(PB6) for I2C1
  
  while(1) {

    ssd1306_init();
    // end of init
    grBuffer_clear_all();
    grBuffer_rectangle(0,0,127,30);
    grBuffer_rectangle(0,33,127,63);
    ssd1306_data_array();

   // ssd1306_clear(0,0,127,7);

    //  one_wire_SEARCH_ROM();
    //  one_wire_MATCH_ROM(sensor_0);
    //  ds18b20_write_scratchpad(0x48,0x01,0x1f);
    //  one_wire_MATCH_ROM(sensor_0);
    //  ds18b20_read_scratchpad();
  }
  return 0;
}

