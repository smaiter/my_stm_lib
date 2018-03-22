//18b20 thermosensor source file
//author: alexand_dm
//version 0.1: created 20.02.18
#include <ds18b20.h>

volatile char ds18b20_scratchpad_register[9];

void ds18b20_convert_t()
{
  one_wire_tx(0x44);
  //while(one_wire_rx_bit()==0);
}

/*--------------------------------------------------
 *@name: one_wire_tx
 *@brief: write TH TL and config register to ds18b20 sensor
 *@param[in]: TH(hight alarm), TL(low alarm), configuration register(sensor resolution) 
 *@return 
 *--------------------------------------------------*/
void ds18b20_write_scratchpad(char TH, char TL, char conf_reg)
{
  one_wire_tx(0x4e);
  one_wire_tx(TH);
  one_wire_tx(TL);
  one_wire_tx(conf_reg);
}

/*--------------------------------------------------
 * @name: ds18b20_read_scratchpad
 * @brief: read all scratchpad of ds18b20:
 *  [0]- temperature LSB;
 *  [1]- temperature MSB;
 *  [2]- Th register; 
 *  [3]- Tl register;
 *  [4]- configuration register;  
 *  [5-7]- reserved;
 *  [8]- CRC
 * @return: 
 *--------------------------------------------------*/
void ds18b20_read_scratchpad() {
  one_wire_tx(0xbe);
  for (int byte=0; byte<=8; byte++)
  {
    ds18b20_scratchpad_register[byte]=one_wire_rx();
  }
}

