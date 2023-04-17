#include <limine/limine.h>

void set_framebuf(struct limine_framebuffer* buf);

void set_pixel(int, int, uint32_t);
uint32_t get_pixel(int, int);
void clear();

void draw_rect(int, int, int, int, uint32_t);

void draw_hline(int, int, int, uint32_t);
void draw_vline(int, int, int, uint32_t);