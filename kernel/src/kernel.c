#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>

void _kstart(multiboot_info_t *mboot_info)
{
    mb_info = mboot_info;
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
    init_keyboard();
    __asm__ __volatile__("sti");

    while (1)
        ;
}
