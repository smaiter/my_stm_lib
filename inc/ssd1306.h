//SSD1306 header file
//author: alexand_dm
//version 0.1: created 2018-03-05 

/**--------------------------------------------------
 *@name: ssd1306_command
 *@brief: send to ssd1306 one byte of command
 *@param[in]: uint16_t comm
--------------------------------------------------*/
void ssd1306_command(uint16_t comm);

/**--------------------------------------------------
 *@name ssd1306_data
 *@brief send to ssd1306 one byte of data
 *@param[in]: uint16_t data 
--------------------------------------------------*/
void ssd1306_data(uint16_t data);

/**--------------------------------------------------
 *@name: ssd1306_clear
 *@brief: clear square (set 0x00 to GDDRAM)
 *@param[in]: col_start, start column (X1 coord.)
 *@param[in]: page_start, start page (Y1 coord.)
 *@param[in]: col_end, end column (X2 coord.)
 *@param[in]: page_end, end page (Y2 coord.)
--------------------------------------------------*/
void ssd1306_clear (char col_start, char page_start, char col_end, char page_end);
