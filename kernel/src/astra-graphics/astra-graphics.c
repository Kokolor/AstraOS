#include "astra-graphics.h"

int cursor_x = 0;
int cursor_y = 0;

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

void set_pixel(int x, int y, uint32_t color)
{
    unsigned *backbuffer = (unsigned *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
    backbuffer[x] = color;
}

int get_pixel(int x, int y)
{
    unsigned int *backbuffer = (unsigned int *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
    return backbuffer[x];
}

void set_rect(int x, int y, int width, int height, uint32_t color)
{
    for (int i = y; i < y + height; i++)
    {
        for (int _i = x; _i < x + width; _i++)
        {
            set_pixel(_i, i, color);
        }
    }
}

void put_rounded_rect(int x, int y, int width, int height, uint32_t color, int radius)
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

void set_lolcat()
{
    int width = 1280;
    int heigth = 720;

    for (int y = 0; y < heigth; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r = (x * y) % 256;
            int g = (x * y * 2) % 256;
            int b = (x * y * 4) % 256;
            set_pixel(x, y, (r << 16) | (g << 8) | b);
        }
    }
}

void scroll_up()
{
    for (int y = 0; y < 720 - 8; y++)
    {
        for (int x = 0; x < 1280; x++)
        {
            int color = get_pixel(x, y + 8);
            set_pixel(x, y, color);
        }
    }
    set_rect(0, 720 - 8, 1280, 8, 0x000000);
    swap_buffers();
}

void put_char(char c, int x, int y, uint32_t color)
{
    uint8_t *offset = font_1 + sizeof(font_header_t) + 16 * c;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (offset[i] & (1 << j))
            {
                set_pixel(x + 8 - j, y + i, color);
            }
        }
    }
}

void put_string(char *string, uint32_t color)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == '\n')
        {
            cursor_x = 0;
            cursor_y += CHAR_HEIGHT;
            if (cursor_y >= 720)
            {
                scroll_up();
                cursor_y -= CHAR_HEIGHT;
            }
        }
        else
        {
            put_char(string[i], cursor_x, cursor_y, color);
            cursor_x += CHAR_WIDTH;
            if (cursor_x >= 1280)
            {
                cursor_x = 0;
                cursor_y += CHAR_HEIGHT;
                if (cursor_y >= 720)
                {
                    scroll_up();
                    cursor_y -= CHAR_HEIGHT;
                }
            }
        }
    }
}

void clear_screen(uint32_t color)
{
    cursor_x = 0;
    cursor_y = 0;

    for (unsigned y = 0; y < mb_info->framebuffer_height; ++y)
    {
        for (unsigned x = 0; x < mb_info->framebuffer_width; ++x)
            set_pixel(x, y, color);
    }
}

void swap_buffers()
{
    memcpy(mb_info->framebuffer_addr, mb_info->framebuffer_addr + mb_info->framebuffer_height * mb_info->framebuffer_pitch, mb_info->framebuffer_pitch * mb_info->framebuffer_height);
}