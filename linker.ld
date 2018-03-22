/* модифицированный ех5 немоляев */
ENTRY(_start);
MEMORY {
        ROM (RX) : ORIGIN = 0x8000000 LENGTH = 64K
        RAM (RW) : ORIGIN = 0x020000000 LENGTH = 20K
       }
SECTIONS  {
            .text : 
            {
              * (.text);
            } > ROM

            .bss :
            {
              * (.bss);
            } > RAM
          }
