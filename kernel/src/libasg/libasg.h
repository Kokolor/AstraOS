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
void flush();