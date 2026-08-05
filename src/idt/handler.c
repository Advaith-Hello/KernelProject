#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "vga/print.h"



__attribute__((cdecl)) void idt_exception_handler(registers_t* regs)
{
  if (regs->vector == 0x21) { 
    uint8_t scancode = inb(0x60);
    print_uint8(scancode);
    print(" ");
  }

  // Acknowledge PIC

  if (regs->vector >= 0x20 && regs->vector <= 0x2F)
  {
    if (regs->vector >= 0x28) {
      outb(0xA0, 0x20); // Send to slave as well
    }
    outb(0x20, 0x20); // Send to master
  }
}

