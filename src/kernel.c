#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "gdt/gdt.h"
#include "vga/print.h"
#include "serial/serial.h"
#include "keyboard/stdin.h"
#include "shell/init/shell.h"
#include "paging/paging.h"


// General cross compiler check

#if !defined(__i686__)
  #error "Do not compile without a cross compiler (see README)"
#endif


// Kernel

void kernel_main(void)
{
	setup_gdt();
	setup_idt();
	setup_paging();
	begin_shell();

  while (1) {
    __asm__ __volatile__("hlt");
  }
}

