#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <libframebuf/libframebuf.h>
#include <libframebuf/libfbfonts.h>
#include <libframebuf/libfbbitmaps.h>
#include <lib/lib.h>

// TODO : Make bitmaps work in LibFrameBuffer

uint8_t menubmp[] = {
    0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000,
    0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000,
    0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000,
    0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000
};

void _kstart(multiboot_info_t *mboot_info)
{
    init_serial();
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
    init_keyboard();
    init_libframebuf(mboot_info);

    int frames = 0;

    bitmap_t *ml;
    
    ml->width = 4;
    ml->height = 4;
    ml->rawdata[16] = menubmp;

    while (1)
    {
        //hi
        
        clear();

        draw_roundrect(100, 100, 100, 100, 7, 0xFFFFFF);

        draw_string("Hi, the World!", 110, 110, 0x000000);

        swap_framebuffers();

        frames++;
    }
}
