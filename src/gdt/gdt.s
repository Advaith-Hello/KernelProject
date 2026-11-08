.global gdt_flush
.extern gdt_ptr


gdt_flush:
    // Load the GDT
    lgdt gdt_ptr

    // Reload important registers
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    // Far jump will reload the CS register
    ljmp $0x08, $flush_done


flush_done:
    ret

