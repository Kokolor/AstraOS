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
    Color color1 = {255, 0, 255, 55};
    Color color2 = {255, 0, 0, 0};

    init_serial();
    printres(mboot_info);
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
    init_mm(mboot_info);
    init_libasg(mboot_info);
    //clear_screen(color1);

    Font my_font;
    my_font.charwidth = DEFAULTFONT_CHARWIDTH;
    my_font.charheight = DEFAULTFONT_CHARHEIGHT;
    my_font.rawdata = defaultfont;
    
    Image my_image;
    my_image.width = DVDVIDEOLOLOL_WIDTH;
    my_image.height = DVDVIDEOLOLOL_HEIGHT;
    my_image.pixels = (uint32_t *)dvdvideololol;
    
    int movetoleft = 0;
    int movetotop = 0;
    int rectx = 0;
    int recty = 0;

    while (1)
    {
        if (rectx == mboot_info->framebuffer_width - DVDVIDEOLOLOL_WIDTH)
        {
            movetoleft = 1;
        }
        else if (rectx == 0)
        {
            movetoleft = 0;
        }
        if (movetoleft == 1)
        {
            rectx--;
        }
        else
        {
            rectx++;
        }
        if (recty == mboot_info->framebuffer_height - DVDVIDEOLOLOL_HEIGHT)
        {
            movetotop = 1;
        }
        else if (recty == 0)
        {
            movetotop = 0;
        }
        if (movetotop == 1)
        {
            recty--;
        }
        else
        {
            recty++;
        }

        set_rect(0, 0, mboot_info->framebuffer_width, mboot_info->framebuffer_height, color1);

        set_image(&my_image, rectx, recty);

        set_string("AstraOS (Made by Kokolor, RaphMar2021)\nLibASG test", 10, 10, &my_font, color2);
        //set_char('d', 100, 100, &my_font, color2);
        flush();
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