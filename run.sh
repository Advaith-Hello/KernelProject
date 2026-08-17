qemu-system-i386 -m 64 -cdrom bin/myos.iso -boot d -D ./qemu.log -d int,cpu_reset,guest_errors
#qemu-system-i386 -kernel bin/kernel.bin -D ./qemu.log -d int,cpu_reset,guest_errors

