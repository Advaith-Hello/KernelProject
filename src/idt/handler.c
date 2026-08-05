#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "vga/print.h"



__attribute__((cdecl)) void idt_exception_handler(registers_t* regs)
{
  if (regs->vector == 0x21) { 
    uint8_t scancode = inb(0x60);
    char chr = (char)scancode;
    terminal_put(scancode);
  }

  if (regs->vector >= 32 && regs->vector <= 47)
  {
    if (regs->vector >= 40) {
      outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
  }
}

