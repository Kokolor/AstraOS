#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <lib/lib.h>
#include <res/res.h>
#include <libasg/libasg.h>

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
    init_libasg(mboot_info);
    //init_libframebuf(mboot_info);

    asm volatile("sti");

    int frames = 0;
    char *frmstr;

    Bitmap b;
    b.width = SUCC_WIDTH;
    b.height = SUCC_HEIGHT;
    b.rawdata = succ;

    Color c;
    c.a = 255;
    c.r = 0;
    c.g = 0;
    c.b = 0;

    while (1)
    {
        set_rect(0,0, mboot_info->framebuffer_width, mboot_info->framebuffer_height, c);

        set_bitmap(100, 100, b);

        flush();
    }
}
