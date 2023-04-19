#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <lib/lib.h>
#include <libasg/libasg.h>

void _kstart(multiboot_info_t *mboot_info)
{
    init_libasg(mboot_info);
    Color color1 = {255, 0, 0};
    Color color2 = {0, 255, 255};
    set_rect(15, 15, 35, 35, color1);
    set_circle(75, 75, 25, color2);
    flush();

    while (1);
}
