CROSS = i686-elf-
CC = $(CROSS)gcc
AS = $(CROSS)as

CFLAGS = -std=gnu11 -ffreestanding -O2 -Wall -Wextra -I./src/
LDFLAGS = -T linker.ld -ffreestanding -nostdlib -lgcc

KERNEL = bin/kernel.bin

SRC := $(shell find src -name "*.c")
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

.PHONY: all clean multiboot

all: kernel multiboot iso

$(KERNEL): $(OBJ) build/boot.o
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/boot.o: src/boot.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

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

