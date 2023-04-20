#include <multiboot/multiboot.h>
#include <lib/lib.h> // memcpy and pow
#include <memory/memory.h> // malloc
#include <stdint.h>

extern int cursorx;
extern int cursory;

typedef struct
{
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct
{
    uint32_t *pixels;
    uint32_t width;
    uint32_t height;
} Image;

typedef struct
{
    int charwidth;
    int charheight;
    uint8_t *rawdata;
} Font;

typedef struct
{
    uint8_t magic[2];
    uint8_t mode;
    uint8_t height;
} FontHeader;

void init_libasg(multiboot_info_t *info);
void clear_screen(Color color);
void set_pixel(int x, int y, Color color);
Color get_pixel(int x, int y);
void set_rect(int x, int y, int width, int height, Color color);
void set_image(Image *image, int x, int y);
Image create_image(uint32_t *data, uint32_t width, uint32_t height);
void set_round_rect(int x, int y, int width, int height, int radius, Color color);
void set_circle(int x0, int y0, int radius, Color color);
void set_char(char c, int x, int y, Font *f, Color col);
void set_string(char *s, int x, int y, Font *f, Color col);
void flush();