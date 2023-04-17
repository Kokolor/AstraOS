#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <serial/serial.h>
#include <lib/libframebuf.h>

void _kstart(multiboot_info_t *mboot_info)
{
    serial_puts("[AstraOS:Kernel] Starting kernel initialization...\n");
    init_serial();
    
    init_libframebuf(framebuffer);
    draw_rect(100, 100, 100, 100, 0xFFFFFF);
    draw_hline(100, 250, 100, 0xFFFFFF);
    draw_vline(100, 300, 100, 0xFFFFFF);

    serial_puts("[AstraOS:Kernel] Starting GDT initialization...");
    init_gdt();
    serial_puts(" OK\n");
    serial_puts("[AstraOS:Kernel] Starting IDT initialization...");
    init_idt();
    init_isr();
    init_irq();
    init_keyboard();
    __asm__ __volatile__("sti");
    serial_puts(" OK\n");
    serial_puts("[AstraOS:Kernel] Kernel has been initialized. Locking up in a while...\n");

    while (1);
}
