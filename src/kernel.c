#include <stdbool.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/print.h"
#include "idt/idt.h"


// General cross compiler check

#if !defined(__i386__)
  #error "Do not compile without a cross compiler (see README)"
#endif


// Kernel

void kernel_main(void)
{
	setup_idt_table();
  init_vga_terminal();

  while (1) {
    __asm__ __volatile__("hlt");
  }
}

