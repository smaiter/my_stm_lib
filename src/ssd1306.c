//SSD1306 source file
//author: alexand_dm
//version 0.1: created 2018-03-05 
#include <stdint.h>
#include <i2c.h>
#include <ssd1306.h>
#include <grbuf.h>

extern uint8_t grBuffer[128][8];

void ssd1306_command(uint16_t comm){
  I2C1->DR=0x80;
  while (!(I2C1->SR1 & 0x4))
  {
    asm("nop");
  }

  I2C1->DR=comm;
  while (!(I2C1->SR1 & 0x4))
  {
    asm("nop");
  }
}

void ssd1306_data(uint16_t data){
  I2C1->DR=0xc0;

  while (!(I2C1->SR1 & 0x4)){
    asm("nop");
  }

  I2C1->DR=data;

  while (!(I2C1->SR1 & 0x4)){
    asm("nop");
  }
}

void ssd1306_data_array(){
  i2c1_start();
  i2c1_slave_adr(0x78);

  ssd1306_command(0x20);
  ssd1306_command(0x00); //Horizontal addresing

  ssd1306_command(0x21); //set column address
  ssd1306_command(0);
  ssd1306_command(127);

  ssd1306_command(0x22); //set page address
  ssd1306_command(0);
  ssd1306_command(7);

  I2C1->DR=0x40; //mode array of data 

  while (!(I2C1->SR1 & 0x4)){
    asm("nop");
  }

  //send graphical buffer to ssd1306
  for (int j = 0; j <= 7; j++) {
    for (int i = 0;  i<= 127; i++) {
      I2C1->DR=grBuffer[i][j];

      while (!(I2C1->SR1 & 0x4)){
        asm("nop");
      }
    }
  }

  //stop the i2c transmission
  i2c1_stop();
}
  

void ssd1306_clear (char col_start, char page_start, char col_end, char page_end){
  i2c1_start();
  i2c1_slave_adr(0x78);
  
  ssd1306_command(0x20);
  ssd1306_command(0x00); //Horizontal addresing

  ssd1306_command(0x21); //set column address
  ssd1306_command(col_start);
  ssd1306_command(col_end);

  ssd1306_command(0x22); //set page address
  ssd1306_command(page_start);
  ssd1306_command(page_end);

  for (int i=0; i<=(col_end - col_start +1) * (page_end - page_start +1); i++){
    ssd1306_data(0x00);
  }

  i2c1_stop();
}

void ssd1306_init(){
  i2c1_start();
  i2c1_slave_adr(0x78);

  ssd1306_command(0xA8);
  ssd1306_command(0x3f);

  ssd1306_command(0xd3);
  ssd1306_command(0x00);

  ssd1306_command(0x40);

  ssd1306_command(0xa1);

  ssd1306_command(0xc8);

  ssd1306_command(0xda);
  ssd1306_command(0x12);

  ssd1306_command(0x81);
  ssd1306_command(0x7f);

  ssd1306_command(0xa4);

  ssd1306_command(0xa6);

  ssd1306_command(0xd5);
  ssd1306_command(0x80);

  ssd1306_command(0x8d);
  ssd1306_command(0x14);

  ssd1306_command(0xaf);

  i2c1_stop();
}
