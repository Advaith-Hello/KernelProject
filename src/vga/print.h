#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/vga_constants.h"
#include "core/utils.h"



void init_vga_terminal(void);
void terminal_put(char chr);

void vga_puts(const char* str);
void vga_puts_hex(const unsigned int hex);
void vga_puts_uint8(const uint8_t hex);

