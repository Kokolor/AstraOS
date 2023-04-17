SRCS := $(shell find kernel/ -name '*.c') 
OBJS := $(SRCS:.c=.o)
CC = gcc
LD = ld

CFLAGS :=                  \
    -Ikernel/src	        \
	-fpermissive			\
    -ffreestanding          \
    -fno-stack-protector    \
    -fno-pic                \
	-w						\
    -O1                     \
    -m32                    \
    -g                      \

ASM_FLAGS :=                \
    -f elf32

LD_FLAGS :=                 \
    -nostdlib               \
    -Tkernel/link.ld        \
	-m elf_i386				\
    -z max-page-size=0x1000

.SUFFIXE: .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.elf: $(OBJS)
	make asm
	$(LD) $(LD_FLAGS) $(OBJS) entry.o -o $@

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

clean:
	rm -f $(OBJS)
	rm *.o
	rm -f kernel.elf
	rm -f astra.iso

asm:
	nasm -f elf32 kernel/src/entry.asm -o entry.o

run:
	make iso
	qemu-system-i386 -m 128M -enable-kvm -serial stdio -cdrom ./astra.iso
