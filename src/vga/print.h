#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/vga_constants.h"
#include "core/utils.h"



void init_vga_terminal(void);
void terminal_put(char chr);

void print(const char* str);
void print_hex(const unsigned int hex);
void print_uint8(const uint8_t hex);

