#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"
#include "vga/print.h"
#include "keyboard/stdin.h"



idt_entry_t idt[256];
static idtr_t idtr;

static bool vectors[IDT_MAX_DESCRIPTORS];
extern void* isr_stub_table[];


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_t* descriptor = &idt[vector]; 

    descriptor->isr_low     = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs   = 0x08;
    descriptor->attributes  = flags;
    descriptor->isr_high    = (uint32_t)isr >> 16;
    descriptor->reserved    = 0;
}


void PIC_remap(int offset1, int offset2)
{
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 1 << CASCADE_IRQ);        // ICW3: tell Master PIC that there is a slave PIC at IRQ2
	io_wait();
	outb(PIC2_DATA, CASCADE_IRQ);             // ICW3: tell Slave PIC its cascade identity
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Unmask both PICs.
	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 0);
}


void setup_idt(void)
{
  idtr.base = (uintptr_t)&idt[0];
  idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

  for (int vector = 0; vector < IDT_MAX_DESCRIPTORS; vector++) {
    idt_set_descriptor(vector, isr_stub_table[(uint8_t)vector], 0x8E);
    vectors[(uint8_t)vector] = true;
  }

	init_keyboard_streams();
  PIC_remap(0x20, 0x28);

  __asm__ __volatile__("lidt %0" : : "m"(idtr)); // load the new IDT
  __asm__ __volatile__("sti"); // set the interrupt flag
  
	outb(PIC1_DATA, 0xFD);
	outb(PIC2_DATA, 0xFF);
}

