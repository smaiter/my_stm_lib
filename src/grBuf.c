//graphical buffer source file
//author: alexand_dm
//version 0.1: created 2018-03-13
#include <stdint.h>
#include <grBuf.h>
#include <font_arial_8pt.h>
uint8_t grBuffer[WIDTH+1][HEIGHT/8]; 

static uint8_t cur_pos_x = 0;
static uint8_t cur_pos_y = 0;

void grBuffer_line_vertical(int x0, int y0, int y1) {
  for (int i = 0; i<= (y1-y0); i++) {
    grBuffer_pixel(x0, y0+i);
  }
}

void grBuffer_line_horizontal(int x0, int y0, int x1){
  for (int i = 0; i <= (x1-x0); i++) {
    grBuffer_pixel(x0+i,y0);
  }
}

void grBuffer_rectangle(int x0, int y0, int x1, int y1) {
  grBuffer_line_horizontal(x0, y0, x1);
  grBuffer_line_horizontal(x0, y1, x1);
  grBuffer_line_vertical(x0, y0, y1);
  grBuffer_line_vertical(x1, y0, y1);
}
 
void grBuffer_clear_all() {
  for (int j=0; j<=HEIGHT; j++){
    for (int i=0; i<=WIDTH; i++) {
      grBuffer[i][j]=0;
    }
  }
}

void grBuffer_print_char(uint8_t symbol) {

  uint8_t width = font_arial_8ptDescriptors[symbol-33][0]; //width of the printing symbol
  int8_t height = font_arial_8ptInfo[4]; //real height of the printing symbol
  uint16_t bitmap = font_arial_8ptDescriptors[symbol-33][1]; //offset of printing symbol 
  uint8_t bit_pos; 
  uint8_t bit_pos_max;

  cur_pos_y = cur_pos_y - height; //set cursor to the top-left positon of character

  while (height >0) {

    if (height>=8) 
      bit_pos_max=7;   //7 becouse count from 0 to 7, not from 1 to 8 
    else 
      bit_pos_max=height-1;

    for (char column = 0; column <= width-1; column++) {
      for (bit_pos = 0; bit_pos <= bit_pos_max ; bit_pos++) {
        if ((font_arial_8ptBitmaps[bitmap]>>bit_pos) & 0x1) 
          grBuffer_pixel(cur_pos_x + column, cur_pos_y + bit_pos);
      } 
      bitmap++;
    } 
    height=height -8;
  }
}

void grBuffer_cur_pos(uint8_t x, uint8_t y) {
  //bottom left position of the character
  cur_pos_x = x;
  cur_pos_y = y;
}

void grBuffer_pixel(int x, int y){
    grBuffer[x][y/8] |= (1 << (y & 7));
}
