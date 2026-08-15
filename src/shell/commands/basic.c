#include "shell/commands/commands.h"
#include "vga/print.h"


int echo_cmd(const char *argument) {
  print(argument);
  return 0;
}

