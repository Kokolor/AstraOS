#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <libframebuf/libframebuf.h>
#include <libframebuf/libfbfonts.h>
#include <lib/lib.h>

void _kstart(multiboot_info_t *mboot_info)
{
    init_serial();
    init_gdt();
    init_libframebuf(mboot_info);

    int frames = 0;

    while (1)
    {
        clear();

        draw_roundrect(100, 100, 100, 100, 7, 0xFFFFFF);

        draw_string("Hi, the World!", 110, 110, 0x000000);
        
        swap_framebuffers();

        frames++;
    }
}
