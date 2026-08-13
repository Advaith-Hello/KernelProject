#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/vga_constants.h"


size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);

int hex_to_str(const unsigned int num, char *str);
int uint8_hex_to_str(const uint8_t num, char *str); 


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

