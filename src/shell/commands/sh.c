#include "shell/commands/commands.h"
#include "vga/print.h"
#include "core/utils.h"


int sh_cmd(const char *input)
{
  char command  [256] = {0};
  char argument [256] = {0};

  int argnum = 0;
  int j = 0;

  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == ' ' || input[i] == '\n') {
      argnum = 1;
      j = 0;
      continue;
    }
    if (argnum == 0) command[j]  = input[i];
    if (argnum == 1) argument[j] = input[i];
    j++;
  }

  if (strcmp(command, "echo") == 0) {
    return echo_cmd(argument);
  } else {
    print("Unknown or undefined command: ");
    print(command);
    print("\n");
    return 2;
  }

  return 0;
}

