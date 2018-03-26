//graphical buffer header file
//author: alexand_dm
//version 0.1: created 2018-03-16 

//---width and height of graphical buffer
#define WIDTH                   127
#define HEIGHT                  64

#define ABS(arg)                ((arg)>0 ? (arg) : -(arg))

//-------------------------Function prototype-------------------------

void grBuffer_pixel(int x, int y);
/**--------------------------------------------------
 @brief: draw one pixel in "x" "y" coordinate
 @param[in]: x and y coordinates of pixel
 --------------------------------------------------*/

void grBuffer_line_horizontal(int x0, int y0, int x1);
/**-------------------------------------------------
 *@brief: draw horizontal line from x0 y0 to x1
 *@param[in]: x0: x start coordinate (right)
              y0: y start coordinate
              x1: x end coordinate (left)
 --------------------------------------------------*/

void grBuffer_line_vertical(int x0, int y0, int y1);
/**-------------------------------------------------
 *@brief: draw vertical line from x0 y0 to x1
 *@param: x0: x start coordinate (up)
 *@param: y0: y start coordinate
 *@param: y1: y end coordinate (bottom)
 --------------------------------------------------*/

void grBuffer_rectangle(int x0, int y0, int x1, int y1);
/**-------------------------------------------------
 *@brief: draw rectangle from x0 y0 to x1 y1
 *@param: x0: x start coordinate (up-right)
 *@param: y0: y start coordinate (up-right)
 *@param: x1: x end coordinate (bottom-left)
 *@param: y1: y end coordinate (bottom-left)
 --------------------------------------------------*/

void grBuffer_print_char(uint8_t symbol);


void grBuffer_clear_all();
/**--------------------------------------------------
 *@brief: clear all graphical buffer (set 0)
--------------------------------------------------*/
