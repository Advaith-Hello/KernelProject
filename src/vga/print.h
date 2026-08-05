#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/vga_constants.h"
#include "core/utils.h"



void init_vga_terminal(void); 
void print(const char* str);
void terminal_put(char chr);

