#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "vga/print.h"

#include "keyboard/scancodes.h"
#include "keyboard/ascii.h"



__attribute__((cdecl)) void idt_exception_handler(registers_t* regs)
{
  if (regs->vector == 0x21) { 
    uint8_t scancode = inb(0x60);
    if (scancode <= 0x58) {
      uint8_t keycode = scan_to_key_table[scancode];
      char chr = keycodes_to_ascii_normal[keycode];
      if (chr) terminal_put(chr);
    }
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

