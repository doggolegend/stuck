# BOOT AND KERNEL

nasm -f bin "src/boot/bootloader.asm" -o "build/bootloader.bin"
nasm -f bin "src/boot/zeroes.asm" -o "build/zeroes.bin"
gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/kernel.c" -o "build/kernel.o" -m32

# DRIVERS

gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/drivers/video.c" -o "build/video.o" -m32
gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/drivers/IO.c" -o "build/IO.o" -m32
nasm -f elf32 "src/drivers/IO.asm" -o "build2/IO.o"

# GDT and HAL

gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/hal/hal.c" -o "build/hal.o" -m32
gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/GDT/gdt.c" -o "build/gdt.o" -m32
nasm -f elf32 "src/GDT/gdt.asm" -o "build2/gdt.o"

# IDT

gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/IDT/idt.c" -o "build/idt.o" -m32
nasm -f elf32 "src/IDT/idt.asm" -o "build2/idt.o"

# ISR

gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/IDT/ISR/isr.c" -o "build/isr.o" -m32
nasm -f elf32 "src/IDT/ISR/isr.asm" -o "build2/isr.o"

# KERNEL PANIC

#gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/kernel_panic.c" -o "build/kernel_panic.o" -m32
nasm -f elf32 "src/kernel_panic.asm" -o "build/kernel_panic.o"

# CRASH TESTING

nasm -f elf32 "src/crash_test.asm" -o "build/crash_test.o"

# PIC
gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/drivers/pic.c" -o "build/pic.o" -m32

# IRQ
gcc  -ffreestanding -fno-stack-protector  -fno-pie -c "src/drivers/irq.c" -o "build/irq.o" -m32

# MERGE

nasm  -f elf32 "src/boot/kernel_entry.asm" -o "build/kernel_entry.o"
ld  -melf_i386 -o "build/kernel.bin" -Ttext 0x1000 "build/kernel_entry.o" "build/kernel.o" "build/video.o" "build/IO.o" "build/gdt.o" "build/hal.o"  "build2/gdt.o" "build/idt.o" "build2/idt.o" "build/isr.o" "build2/isr.o" "build/kernel_panic.o" "build/crash_test.o" "build2/IO.o" "build/pic.o" "build/irq.o" --oformat binary -T link.ld
cat "build/bootloader.bin" "build/kernel.bin" "build/zeroes.bin" > os.img

# EMULATE

qemu-system-x86_64 os.img