#include <stdint.h>
#include <multiboot/multiboot.h>

void init_libframebuf(multiboot_info_t* buf);

void setpixel(int, int, uint32_t);
uint32_t getpixel(int, int);
void clear();

void draw_rect(int, int, int, int, uint32_t);
void draw_roundrect(int, int, int, int, int, uint32_t);

void draw_hline(int, int, int, uint32_t);
void draw_vline(int, int, int, uint32_t);

void swap_framebuffers();