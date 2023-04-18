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

void drawbitmap(uint32_t *rawdata, int width, int height, int x, int y)
{
    /**for (int y2 = y; y2 < height; y2++)
    {
        for (int x2 = x; x2 < width; x2++)
        {   
            uint32_t *col = rawdata[x2 + (y2 * width)];
            setpixel(x + x2, y + y2, col);
            swap_framebuffers();
            
        }
    }**/
    
    for (uint32_t i = y; i < y + height; i++) {
        for (uint32_t j = x; j < x + width; j++) {
            uint32_t color_in = ((uint32_t*)rawdata)[(i - y) * width + (j - x)];
            uint32_t color_out = 0;

            color_out |= (color_in & 0xff000000);
            color_out |= ((color_in & 0x00ff0000) >> 16);
            color_out |= (color_in & 0x0000ff00);
            color_out |= ((color_in & 0x000000ff) << 16);

            setpixel((int)j , (int)i, color_out);
        }
    }

}