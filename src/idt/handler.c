#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"


#define PS2_DATA_PORT   0x60
#define PS2_STATUS_PORT 0x64
#define PIC1_COMMAND    0x20
#define PIC_EOI         0x20



void idt_exception_handler(registers_t* regs) {
  switch (vector)
  {
    case 0x20:

      if (inb(PS2_STATUS_PORT) & 0x01) {return;}
      
      uint8_t scancode = inb(PS2_DATA_PORT);
      
      outb(PIC1_COMMAND, PIC_EOI);
      break;
  }
}

