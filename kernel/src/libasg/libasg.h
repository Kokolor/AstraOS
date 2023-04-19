#include <multiboot/multiboot.h>
#include <stdint.h>

typedef struct
{
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct
{
    uint8_t *rawdata;
    int width;
    int height;
} Bitmap;

void init_libasg(multiboot_info_t *info);