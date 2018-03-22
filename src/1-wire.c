/*--------------------------------------------------
 * 1-wire source file
 * author: alexand_dm
 * version 0.1: created 06.02.18
 * version 0.2: 20.02.18, add SEARCH_ROM, MATCH_ROM
 *--------------------------------------------------*/

#include "gpio.h"
#include "systick.h"
#include "1-wire.h"
volatile int one_wire_buffer; //8bit buffer
volatile char one_wire_register[8]; 
volatile char one_wire_sensor[NUM_OF_SENSORS][8];

void DQ_free ()
{
  DQ_STATE=((DQ_STATE)& ~(0b1111<<PIN_BIT_NUM))|(input_fl<<PIN_BIT_NUM);
}

void DQ_null ()
{
  DQ_STATE=((DQ_STATE) & ~(0b1111<<PIN_BIT_NUM))|(output_pp<<PIN_BIT_NUM);
  DQ_PORT->BSRR|=(1<<(PIN_BSRR_NUM));
}

void one_wire_tx_bit1()
{
  DQ_null();
  stk_delayUS(8);
  DQ_free();
  stk_delayUS(40);
  return;
}

void one_wire_tx_bit0()
{
      DQ_null();
      stk_delayUS(55);
      DQ_free();
      stk_delayUS(2);
      return;
}

char one_wire_rx_bit()
{
  DQ_null(); 
  stk_delayUS(4); 
  DQ_free();
  stk_delayUS(12);

  if ((DQ_PORT->IDR) & (PIN_NUM))
  {
    stk_delayUS(30);
    return 1;
  }
  else
  {
    stk_delayUS(30);
    return 0;
  }
}

void one_wire_tx(char data)
{
  char i=8;
  while (i)
  {

    if (data & 1)
    {
      DQ_null();
      stk_delayUS(8);
      DQ_free();
      stk_delayUS(40);
    }

    else        //data &1 false
    {
      DQ_null();
      stk_delayUS(55);
      DQ_free();
      stk_delayUS(2);
    }
    data = (data >>1);
    i--;
  }
}

/*--------------------------------------------------
 * @name: one_wire_rx
 * @brief: read one byte from one-wire bus 
 * @return: one_wire_buffer (1-byte)
 *--------------------------------------------------*/
int one_wire_rx()
{
  one_wire_buffer=0;
  char i=8;
  while(i)
  {
    DQ_null(); 
    stk_delayUS(4); 
    DQ_free();
    stk_delayUS(12);

    if ((DQ_PORT->IDR) & (PIN_NUM))
      one_wire_buffer=(one_wire_buffer >> 1) | 0b10000000;
    else
      one_wire_buffer=(one_wire_buffer >> 1);

    stk_delayUS(30);
    i--;
  }
  return one_wire_buffer;
}

/*--------------------------------------------------
 * @name: one_wire_reset
 * @brief: one-wire bus reset
 *--------------------------------------------------*/
void one_wire_reset()
{
  DQ_null();
  stk_delayUS(500);
  DQ_free();
}


void one_wire_presence()
{
  while ((DQ_PORT->IDR & (PIN_NUM))!=0); //wait presence signal(DQ=0)
  stk_delayUS(240);
}

void one_wire_READ_ROM()
{
  one_wire_tx(0x33);
  for (int counter=0; counter<=7;counter++)
  {
    one_wire_register[counter]=one_wire_rx();
  }
}

/*--------------------------------------------------
 *@name one_wire_SEARCH_ROM
 *@brief SEARCH ROM function for one wire bus
 *@param[out] 
 *@return 
 *@TODO do it with pointer, 2018-02-26
--------------------------------------------------*/
void one_wire_SEARCH_ROM() {
  char mismatch_bit=0;

  for (int sensor_num=0; sensor_num<=NUM_OF_SENSORS-1; sensor_num++) {
    char counter_bit=0;
    one_wire_reset();
    one_wire_presence();
    one_wire_tx(0xf0);

    for (int byte_num=0; byte_num<=7; byte_num++) {   //8 byte cycle
    
      for (int bit_num=0; bit_num<=7; bit_num++) {  //1 byte cycle
        char bit_a=one_wire_rx_bit();
        char bit_b=one_wire_rx_bit();

        if (bit_a==0 && bit_b==0) {
          if (counter_bit>mismatch_bit) {
            one_wire_buffer>>=1;
            one_wire_tx_bit0();
            mismatch_bit=counter_bit;
          }
          else {
            one_wire_buffer=one_wire_buffer>>1 |0b10000000;
            one_wire_tx_bit1();
          }
        }
        else {
          if (bit_a==0) {
            one_wire_buffer=one_wire_buffer >>1;
            one_wire_tx_bit0();
          }
          else {
            one_wire_buffer=one_wire_buffer >>1 |0b10000000;
            one_wire_tx_bit1();
          }
        }
        counter_bit++;
      }
      one_wire_sensor[sensor_num][byte_num]=one_wire_buffer;
    }
  }
}

void one_wire_MATCH_ROM(enum num_of_sensor num)
{
  one_wire_reset();
  one_wire_presence();
  one_wire_tx(0x55);

  for (int i=0; i<=7; i++)
    one_wire_tx(one_wire_sensor[num][i]);
}


