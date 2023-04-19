#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <lib/lib.h>
#include <res/res.h>
#include <libasg/libasg.h>

void _kstart(multiboot_info_t *mboot_info)
{
    init_serial();
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
    init_mm(mboot_info);
    init_libasg(mboot_info);

    Image my_image;
    my_image.width = DINDE_RGB_WIDTH;
    my_image.height = DINDE_RGB_HEIGHT;
    my_image.pixels = (uint32_t *)dinde_rgb;

    set_image(&my_image, 0, 0);

    flush();

    while (1);
}
