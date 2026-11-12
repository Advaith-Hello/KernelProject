// Setting multiboot header info

.set ALIGN,       1 << 0
.set MEMINFO,     1 << 1
.set GRAPHICS,    1 << 2
.set FLAGS,       ALIGN | MEMINFO | GRAPHICS
.set MAGIC,       0x1BADB002
.set CHECKSUM,    -(MAGIC + FLAGS)

// Im multiboot trust

.section .multiboot
.align 4

  // Standard multiboot
  .long MAGIC
  .long FLAGS
  .long CHECKSUM

  // Other
  .long 0, 0, 0, 0, 0

  // Video settings
  .long 0
  .long 1024
  .long 768
  .long 32

// Allocates 16 KiB for stack

.section .bss
  .align 16
  stack_bottom:
    .skip (16 * 1024) # 16 KiB
  stack_top:

// Globalizes _start for ENTRY

.section .text
  .global _start
  .type _start, @function

// Jumps to C kernel

_start:
  mov $stack_top, %esp // Sets stack
  push %ebx // Passes grub return data into main
  call kernel_main // Calls the kernel

