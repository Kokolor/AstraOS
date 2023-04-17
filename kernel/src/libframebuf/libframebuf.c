#include "libframebuf.h"
#include <stdint.h>
#include <lib/lib.h>

multiboot_info_t* mboot_info;

void init_libframebuf(multiboot_info_t* mbi)
{
    serial_puts("[AstraOS:Kernel] Initializing LibFrameBuffer...");
    mboot_info = mbi;
    serial_puts(" OK\n");
}

void setpixel(int x, int y, uint32_t col)
{
    unsigned *backbuffer = (unsigned *)(mboot_info->framebuffer_addr + (y + mboot_info->framebuffer_height) * mboot_info->framebuffer_pitch);
    backbuffer[x] = col;
}

uint32_t getpixel(int x, int y)
{
    unsigned int *backbuffer = (unsigned int *)(mboot_info->framebuffer_addr + (y + mboot_info->framebuffer_height) * mboot_info->framebuffer_pitch);
    return (uint32_t)backbuffer[x];
}

void swap_framebuffers()
{
    memcpy(mboot_info->framebuffer_addr, mboot_info->framebuffer_addr + mboot_info->framebuffer_height * mboot_info->framebuffer_pitch, mboot_info->framebuffer_pitch * mboot_info->framebuffer_height);
}

void draw_rect(int x, int y, int width, int height, uint32_t col)
{
    for (int i = y; i < y + height; i++) {
        for (int i2 = x; i2 < x + width; i2++) {
            setpixel(i2, i, col);
        }
    }
}

void draw_roundrect(int x, int y, int width, int height, int radius, uint32_t color)
{
    for (int j = y; j < (y + height); j++)
    {
        for (int i = x; i < (x + width); i++)
        {
            int dx = i - x;
            int dy = j - y;
            if ((dx < radius && dy < radius && pow(dx - radius, 2) + pow(dy - radius, 2) > pow(radius, 2)) ||
                (dx < radius && dy > height - radius && pow(dx - radius, 2) + pow(dy - (height - radius), 2) > pow(radius, 2)) ||
                (dx > width - radius && dy < radius && pow(dx - (width - radius), 2) + pow(dy - radius, 2) > pow(radius, 2)) ||
                (dx > width - radius && dy > height - radius && pow(dx - (width - radius), 2) + pow(dy - (height - radius), 2) > pow(radius, 2)))
            {
            }
            else
            {
                setpixel(i, j, color);
            }
        }
    }
}

void clear()
{
    draw_rect(0, 0, mboot_info->framebuffer_width, mboot_info->framebuffer_height, 0x000000);
}

void draw_hline(int x, int y, int width, uint32_t col)
{
    for (int i = x; i < x + width; i++)
    {
        setpixel(i, y, col);
    }
}

void draw_vline(int x, int y, int height, uint32_t col)
{
    for (int i = y; i < y + height; i++)
    {
        setpixel(x, i, col);
    }
}