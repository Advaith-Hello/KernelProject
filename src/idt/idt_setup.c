#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "idt/idt.h"



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


int setup_idt_table(void)
{
  idtr.base = (uintptr_t)&idt[0];
  idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

  for (uint8_t vector = 0; vector < 32; vector++) {
    idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    vectors[vector] = true;
  }

  __asm__ __volatile__("lidt %0" : : "m"(idtr)); // load the new IDT
  __asm__ __volatile__("sti"); // set the interrupt flag

  return 0;
}

