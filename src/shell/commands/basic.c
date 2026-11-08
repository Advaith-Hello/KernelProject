#include "shell/commands/commands.h"
#include "vga/print.h"


int echo_cmd(const char *argument) {
  vga_puts(argument);
  return 0;
}

