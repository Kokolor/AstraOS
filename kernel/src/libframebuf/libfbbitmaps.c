#include <libframebuf/libframebuf.h>
#include <libframebuf/libfbbitmaps.h>

void draw_bitmap(bitmap_t *bitmap, int x, int y)
{
    for (int y2 = y; y2 < bitmap->height; y2++)
    {
        for (int x2 = x; x2 < bitmap->width; x2++)
        {   
            uint32_t col = bitmap->rawdata[x2 + (y2 * bitmap->width)];
            setpixel(x + x2, y + y2, col);
            swap_framebuffers();
        }
    }
}

void drawbitmap(uint32_t rawdata[], int width, int height, int x, int y)
{
    for (int y2 = y; y2 < height; y2++)
    {
        for (int x2 = x; x2 < width; x2++)
        {   
            uint32_t col = rawdata[x2 + (y2 * width)];
            setpixel(x + x2, y + y2, col);
            swap_framebuffers();
        }
    }
}