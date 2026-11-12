#include "idt/idt.h"
#include "core/utils.h"


void serial_puts(const char *s) {
  while (*s) outb(0x3F8, *s++);
}

void serial_puts_hex(const unsigned int hex) {
  char buffer[9];
  hex_to_str(hex, buffer);
  serial_puts(buffer);
}

