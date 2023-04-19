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

// typedef struct {
//     uint8_t r;
//     uint8_t g;
//     uint8_t b;
// } Color;

// void set_pixel(int x, int y, Color color)
// {
//     unsigned *backbuffer = (unsigned *)(mbi->framebuffer_addr + (y + mbi->framebuffer_height) * mbi->framebuffer_pitch);
//     backbuffer[x] = (color.r << 16) | (color.g << 8) | color.b;
// }

void flush()
{
    memcpy(mbi->framebuffer_addr, mbi->framebuffer_addr + mbi->framebuffer_height * mbi->framebuffer_pitch, mbi->framebuffer_pitch * mbi->framebuffer_height);
}