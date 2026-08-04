CROSS = i686-elf-
CC = $(CROSS)gcc
AS = $(CROSS)as
NASM = nasm

CFLAGS = -std=gnu11 -ffreestanding -O2 -Wall -Wextra -I./src/
LDFLAGS = -T linker.ld -ffreestanding -nostdlib -lgcc

KERNEL = bin/kernel.bin

SRC_C := $(shell find src -name "*.c")
OBJ_C := $(patsubst src/%.c,build/%.o,$(SRC_C))

SRC_ASM := $(shell find src -name "*.asm")
OBJ_ASM := $(patsubst src/%.asm,build/%.o,$(SRC_ASM))

.PHONY: all clean multiboot

all: kernel multiboot iso

$(KERNEL): $(OBJ_C) $(OBJ_ASM) build/boot.o
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

build/%.o: src/%.asm
	mkdir -p $(dir $@)
	$(NASM) -f elf32 $< -o $@

clean:
	rm -rf build bin

multiboot: $(KERNEL)
	grub-file --is-x86-multiboot $(KERNEL)
	@echo "Multiboot valid"

kernel: $(KERNEL)

iso: $(KERNEL)
	mkdir -p bin/iso/boot/grub
	cp bin/kernel.bin bin/iso/boot/myos
	cp grub.cfg bin/iso/boot/grub/grub.cfg
	grub-mkrescue -o bin/myos.iso bin/iso

