//graphical buffer source file
//author: alexand_dm
//version 0.1: created 2018-03-13
#include <stdint.h>
#include <grbuf.h>
uint8_t grBuffer[WIDTH+1][HEIGHT/8]; 

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

void grBuffer_pixel(int x, int y){
    grBuffer[x][y/8] |= (1 << (y & 7));
}
