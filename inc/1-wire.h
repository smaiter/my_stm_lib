//1-wire header file
//author: alexand_dm
//version: 0.1: created 06.02.18
//#include "gpio.h"
#define DQ_PORT       GPIOC
#define PIN_GROUP     CRH
#define PIN_NUM       (1<<14)
#define PIN_BIT_NUM   24 //start number of GPIOx_CRH or GPIOx_CRL pin bit 
#define PIN_BSRR_NUM  30
#define DQ_STATE      DQ_PORT->PIN_GROUP
#define output_pp     0x2
#define input_fl      0x4
#define NUM_OF_SENSORS 2

enum num_of_sensor {sensor_0, sensor_1};
//--------------------Functions protorypes--------------------

void DQ_free();
void DQ_null();
void one_wire_reset();
void one_wire_tx(char data);

int one_wire_rx();
/**--------------------------------------------------
 * @brief: read one byte from one-wire bus 
 * @return: one_wire_buffer (1-byte)
 *--------------------------------------------------*/

void one_wire_READ_ROM();
