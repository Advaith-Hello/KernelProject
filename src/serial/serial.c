#include "idt/idt.h"


void serial_puts(const char *s) {
  while (*s) outb(0x3F8, *s++);
}

