#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <lib/lib.h>
#include <res/res.h>

// TODO : Make bitmaps work in LibFrameBuffer

void _kstart(multiboot_info_t *mboot_info)
{
    init_serial();
    printres(mboot_info);
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
    init_keyboard();
    //init_libframebuf(mboot_info);

    asm volatile("sti");

    int frames = 0;
    char *frmstr;

    while (1)
    {
    }
}

void printres(multiboot_info_t *mbi)
{
    char *width;
    char *height;
    char *bpp;
    itoa(width, mbi->framebuffer_width, 10);

    serial_puts("[AstraOS:Kernel] Framebuffer resolution : ");
    serial_puts(width);
    serial_putc('x');

    itoa(height, mbi->framebuffer_height, 10);

    serial_puts(height);
    serial_putc('x');
    
    itoa(bpp, mbi->framebuffer_bpp, 10);

    serial_puts(bpp);
    serial_putc('\n');

}