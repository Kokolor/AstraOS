#include <multiboot/multiboot.h>
#include <lib/lib.h> // For memcpy

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

void init_libasg(multiboot_info_t *info);
void set_pixel(int x, int y, Color color);
Color get_pixel(int x, int y);
void set_rect(int x, int y, int width, int height, Color color);
void set_circle(int x0, int y0, int radius, Color color);
void flush();