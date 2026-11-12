#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "gdt/gdt.h"
#include "paging/paging.h"
#include "paging/mapping.h"
#include "serial/serial.h"


// General cross compiler check

#if !defined(__i686__)
  #error "Do not compile without a cross compiler (see README)"
#endif


// Kernel

void kernel_main(void* multiboot_info)
{
	// Critical system functions
	
	setup_gdt();
	setup_idt();
	setup_paging();
	
	// Map multiboot_info page

	mmap_physical(multiboot_info, (size_t)116);

	// Get framebuffer data from multiboot_info
	
	uintptr_t fb_addr   = *(uintptr_t *) ((uint8_t *)multiboot_info + 88);
	uint32_t  fb_pitch  = *(uint32_t *)  ((uint8_t *)multiboot_info + 96);
	uint32_t  fb_width  = *(uint32_t *)  ((uint8_t *)multiboot_info + 100);
	uint32_t  fb_height = *(uint32_t *)  ((uint8_t *)multiboot_info + 104);
	uint8_t   fb_bpp    = *(uint32_t *)  ((uint8_t *)multiboot_info + 108);
	uint8_t   fb_type   = *(uint32_t *)  ((uint8_t *)multiboot_info + 109);

	// Map framebuffer
	
	mmap_physical((void*)fb_addr, (size_t)(fb_width * fb_height * 4));
	volatile uint32_t *fb = (volatile uint32_t *)(uintptr_t)fb_addr;

	// Print values
	
	serial_puts_hex(fb_addr);
	serial_puts_hex(fb_pitch);
	serial_puts_hex(fb_width);
	serial_puts_hex(fb_height);
	serial_puts_hex(fb_bpp);
	serial_puts_hex(fb_type);

	// Draw stripes to screen
	
	for (int y = 0; y < fb_height; y++) {
    for (int x = 0; x < fb_width; x++)
    {
    		int stride = fb_pitch / 4;
        int diagonal = ((x + y) / 16) % 3;
        
        if (diagonal == 0) fb[stride * y + x] = 0xFF0000;
        if (diagonal == 1) fb[stride * y + x] = 0x00FF00;
        if (diagonal == 2) fb[stride * y + x] = 0x0000FF;
    }
	}
	
	// Infinite hang

  while (1) {
    __asm__ __volatile__("hlt");
  }
}

