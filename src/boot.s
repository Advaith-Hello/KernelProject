// Setting multiboot header info

.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

// Im multiboot trust

.section .multiboot
  .align 4
  .long MAGIC
  .long FLAGS
  .long CHECKSUM

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
  movw $0x3F8, %dx
  movb $'X', %al
  outb %al, %dx
  mov $stack_top, %esp // Sets stack
  call kernel_main // Calls the kernel

