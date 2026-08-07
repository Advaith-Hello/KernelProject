#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "vga/print.h"

#include "keyboard/stdin.h"
#include "keyboard/scancodes.h"
#include "keyboard/ascii.h"



__attribute__((cdecl)) void idt_exception_handler(registers_t* regs)
{
  // Keyboard interrupts

  if (regs->vector == 0x21)
  {
    uint8_t scancode = inb(0x60);
    bool released = scancode > 0x58;
    uint8_t keycode = scan_to_key_table[scancode & 0x7F];

    if (scancode <= 0x58) {
      uint8_t keycode = scan_to_key_table[scancode];
      char chr = keycodes_to_ascii_normal[keycode];
      if (chr) push_to_key_stream(chr);
    }

    if (keycode >= 0x32 && keycode <= 0x3A) {
      uint8_t control_idx = keycode - 0x33;
      if (released) control_char &= ~(1 << control_idx);
      else control_char |= (1 << control_idx);
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

