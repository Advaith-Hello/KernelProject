#include <stdbool.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/print.h"
#include "idt/idt.h"
#include "keyboard/stdin.h"


// General cross compiler check

#if !defined(__i386__)
  #error "Do not compile without a cross compiler (see README)"
#endif


// Kernel

void kernel_main(void)
{
	setup_idt_table();
  init_vga_terminal();

  print("What is your name? ");

  char name[256] = {0};
  input_stdin(name, sizeof(name));

  print("\nHello, ");
  print(name);

  while (1) {
    __asm__ __volatile__("hlt");
  }
}

