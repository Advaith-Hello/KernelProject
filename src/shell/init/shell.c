#include "shell/init/shell.h"
#include "shell/commands/commands.h"
#include "vga/print.h"
#include "keyboard/stdin.h"



void begin_shell()
{
  init_vga_terminal();

  while (1)
  {
    print("$ ");
    char input[256] = {0};
    input_stdin(input, sizeof(input));
    sh_cmd(input);
  }
}

