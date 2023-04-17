#include <limine/limine.h>
#include <serial/serial.h>
#include "libframebuf.h"

struct limine_framebuffer *buffer;

void init_libframebuf(struct limine_framebuffer* buf)
{
    serial_puts("[LibFrameBuffer] Starting initialization...");
    buffer = buf;
    serial_puts(" OK\n");
}

void set_pixel(int x, int y, uint32_t col)
{
    uint32_t *fb = buffer->address;
    fb[y * buffer->width + x] = col;
}

uint32_t get_pixel(int x, int y)
{
    uint32_t *fb = buffer->address;
    return fb[y * buffer->width + x];
}

void draw_rect(int x, int y, int width, int height, uint32_t col)
{
    for (int i = y; i < y + height; i++) {
        for (int i2 = x; i2 < x + width; i2++) {
            set_pixel(i2, i, col);
        }
    }
}

void clear()
{
    draw_rect(0, 0, buffer->width, buffer->height, 0x000000);
}

void draw_hline(int x, int y, int width, uint32_t col)
{
    for (int i = x; i < x + width; i++)
    {
        set_pixel(i, y, col);
    }
}

void draw_vline(int x, int y, int height, uint32_t col)
{
    for (int i = y; i < y + height; i++)
    {
        set_pixel(x, i, col);
    }
}