#include "gdt/gdt.h"



uint64_t gdt_entries[GDT_ENTRIES_AMT];
struct gdt_pointer gdt_ptr;

extern void gdt_flush();


uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0
 
    return descriptor;
}


void setup_gdt()
{
    // Limit and base for lgdt
    gdt_ptr.limit = (sizeof(uint64_t) * GDT_ENTRIES_AMT) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries[0];

    // Null
    gdt_entries[0] = create_descriptor(0x00000000, 0x0, 0x0);
    
    // Ring 0
    gdt_entries[1] = create_descriptor(0x00400000, 0x003FFFFF, GDT_CODE_PL0);
    gdt_entries[2] = create_descriptor(0x00800000, 0x003FFFFF, GDT_DATA_PL0);
    
    // Ring 3
    gdt_entries[3] = create_descriptor(0x00000000, 0xFFFFFFFF, GDT_CODE_PL3);
    gdt_entries[4] = create_descriptor(0x00000000, 0xFFFFFFFF, GDT_DATA_PL3);

    // Flush in asm
    gdt_flush();
}

