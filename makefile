SRCS := $(shell find kernel/ -name '*.c') 
OBJS := $(SRCS:.c=.o)
CC = gcc
LD = ld

CFLAGS :=                  \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fno-PIE \
    -fno-PIC \
    -m64 \
	-Ikernel/src/ \
    -march=x86-64 \
    -mabi=sysv \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone \
    -mcmodel=kernel                   \

ASM_FLAGS :=                \
    -f elf64

LD_FLAGS :=                 \
    -nostdlib \
    -static \
    -m elf_x86_64 \
    -z max-page-size=0x1000 \
    -T kernel/link.ld

.SUFFIXE: .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.elf: $(OBJS)
	make asm
	$(LD) $(LD_FLAGS) $(OBJS) gdt.o idt.o -o $@

clean:
	rm -f $(OBJS)
	rm -f kernel.elf
    rm *.o
	rm astra.iso

iso:
	rm -rf iso_root
	mkdir -p iso_root
	cp kernel.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o astra.iso
	limine/limine-deploy astra.iso
	rm -rf iso_root

asm:
	nasm -f elf64 -o gdt.o kernel/src/arch/x86_64/gdt.asm
	nasm -f elf64 -o idt.o kernel/src/arch/x86_64/idt.asm

run:
	make iso
	qemu-system-x86_64 -m 128M -enable-kvm -serial stdio -cdrom ./astra.iso
