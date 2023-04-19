#include <libasg/libasg.h>

multiboot_info_t *mbi;

void init_libasg(multiboot_info_t *info)
{
    mbi = info;
}
void set_pixel(int x, int y, Color color)
{
    unsigned *backbuffer = (unsigned *)(mbi->framebuffer_addr + (y + mbi->framebuffer_height) * mbi->framebuffer_pitch);
    backbuffer[x] = (color.r << 16) | (color.g << 8) | color.b;
}

Color get_pixel(int x, int y)
{
    unsigned *backbuffer = (unsigned *)(mbi->framebuffer_addr + (y + mbi->framebuffer_height) * mbi->framebuffer_pitch);
    unsigned color = backbuffer[x];
    return (Color){(color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF};
}

void set_rect(int x, int y, int width, int height, Color color)
{
    for (int i = y; i < y + height; i++)
    {
        for (int _i = x; _i < x + width; _i++)
        {
            set_pixel(_i, i, color);
        }
    }
}

void set_bitmap(int x, int y, Bitmap b)
{
    for (uint32_t i = y; i < b.width; i++) {
        for (uint32_t j = x; j < b.height; j++) {
            uint8_t color = b.rawdata[(i - y) * b.width + (j - x)];
            Color col = (Color){(color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF};
            set_pixel(x + j, y + i, col);
        }
    }
}

void set_round_rect(int x, int y, int width, int height, int radius, Color color)
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
                set_pixel(i, j, color);
            }
        }
    }
}

void set_circle(int x0, int y0, int radius, Color color)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y)
    {
        for (int i = x0 - y; i <= x0 + y; i++)
        {
            set_pixel(i, y0 + x, color);
            set_pixel(i, y0 - x, color);
        }
        for (int i = x0 - x; i <= x0 + x; i++)
        {
            set_pixel(i, y0 + y, color);
            set_pixel(i, y0 - y, color);
        }
        x++;
        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
    }
}

void flush()
{
    memcpy(mbi->framebuffer_addr, mbi->framebuffer_addr + mbi->framebuffer_height * mbi->framebuffer_pitch, mbi->framebuffer_pitch * mbi->framebuffer_height);
}