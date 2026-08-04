#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/vga_constants.h"
#include "core/utils.h"


// General cross compiler check

#if !defined(__i386__)
  #error "Do not compile without a cross compiler (see README)"
#endif

// Terminal VGA variable init

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;


// Init script

void terminal_init(void) 
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
	terminal_buffer[idx] = vga_entry(chr, terminal_color);

	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}


// Write null-term string on screen

void terminal_write(const char* str) {
  size_t size = strlen(str);
	for (size_t i = 0; i < size; i++) {
		terminal_put(str[i]);
	}
}


// Kernel

void kernel_main(void)
{
  terminal_init();
  terminal_write("Hello, World!");

  while (1) {
    __asm__ __volatile__("hlt");
  }
}

