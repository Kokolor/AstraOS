#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <astra-graphics/astra-graphics.h>

void _kstart(multiboot_info_t *mboot_info)
{
    mb_info = mboot_info;
    init_gdt();
    // set_rect(15, 15, 45, 45, 0xff0000);
    set_lolcat();
    put_rounded_rect(75, 75, 255, 255, 0x003f2b, 10);
    cursor_x = 85;
    cursor_y = 85;
    put_string("Hello World!", 0xffffff);
    swap_buffers();

    while (1)
        ;
}
