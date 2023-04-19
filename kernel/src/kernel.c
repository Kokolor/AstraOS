#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <libframebuf/libframebuf.h>
#include <libframebuf/libfbfonts.h>
#include <libframebuf/libfbbitmaps.h>
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
    init_libframebuf(mboot_info);

    asm volatile("sti");

    int frames = 0;
    char *frmstr;

    int rectx = 0;
    int recty = 0;
    int gotoleft = 0;
    int gototop = 0;

    while (1)
    {
        //hi
        
        clear();

        draw_roundrect(100, 100, 100, 100, 7, 0xFFFFFF);

        draw_string("Hi, the World!", 110, 110, 0x000000);

        itoa(frmstr, frames, 10);

        draw_string(frmstr, 10, 690, 0xFFFFFF);

        draw_bitmap(astralogo, ASTRALOGO_WIDTH, ASTRALOGO_HEIGHT, mboot_info->framebuffer_width / 2 - ASTRALOGO_WIDTH / 2, mboot_info->framebuffer_height / 2 - ASTRALOGO_HEIGHT / 2);

        if (rectx == mboot_info->framebuffer_width - DVDVIDEOLOLOL_WIDTH)
        {
            gotoleft = 1;
        }else if (rectx == 0)
        {
            gotoleft = 0;
        }
        
        if (gotoleft == 1)
        {
            rectx--;
        }else
        {
            rectx++;
        }

        if (recty == mboot_info->framebuffer_height - DVDVIDEOLOLOL_HEIGHT)
        {
            gototop = 1;
        }else if (recty == 0)
        {
            gototop = 0;
        }
        
        if (gototop == 1)
        {
            recty--;
        }else
        {
            recty++;
        }

        draw_bitmap(dvdvideololol, DVDVIDEOLOLOL_WIDTH, DVDVIDEOLOLOL_HEIGHT, rectx, recty);
        //draw_rect(rectx, recty, 100, 100, 0xFFFFFF);

        swap_framebuffers();

        frames++;
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