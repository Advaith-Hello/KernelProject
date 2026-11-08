#include "vga/vga_constants.h"
#include "core/utils.h"
#include "vga/print.h"



size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;


void init_vga_terminal(void) 
{
  // Init vars
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	// Loop over the space and zero it
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t idx = y * VGA_WIDTH + x;
      terminal_buffer[idx] = vga_entry(' ', terminal_color);
		}
	}
}


// Put char on screen

void terminal_put(char chr)
{
	const size_t idx = terminal_row * VGA_WIDTH + terminal_column;

  if (chr >= 32 && chr <= 126 && chr != '\n' && chr != '\r') {
	  terminal_buffer[idx] = vga_entry(chr, terminal_color);
	}

	if (chr == '\n') {
		terminal_row++;
		terminal_column = 0;
	} else if (chr == '\r') {
		terminal_column = 0;
	} else {
		terminal_column++;
	}

	if (terminal_column >= VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}

	if (terminal_row >= VGA_HEIGHT) {
		terminal_row = 0;
		terminal_column = 0;
	}
}


// Write null-term string on screen

void vga_puts(const char* str) {
  size_t size = strlen(str);
	for (size_t i = 0; i < size; i++) {
		terminal_put(str[i]);
	}
}


// Prints an int as a hex string

void vga_puts_hex(const unsigned int hex) {
  char buffer[9];
  hex_to_str(hex, buffer);
  vga_puts(buffer);
}

// Prints a uint8_t as a hex string

void vga_puts_uint8(const uint8_t hex) {
  char buffer[3];
  uint8_hex_to_str(hex, buffer);
  vga_puts(buffer);
}

