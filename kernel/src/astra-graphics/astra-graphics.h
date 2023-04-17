#include <stdint.h>
#include <lib/lib.h> // Memcpy and pow
#include <multiboot/boot_info.h> // Multiboot
#include "font.h"

extern int cursor_x;
extern int cursor_y;

void set_pixel(int x, int y, uint32_t color);
int get_pixel(int x, int y);
void set_rect(int x, int y, int width, int height, uint32_t color);
void put_rounded_rect(int x, int y, int width, int height, uint32_t color, int radius);
void set_lolcat();
void scroll_up();
void put_char(char c, int x, int y, uint32_t color);
void put_string(char *string, uint32_t color);
void draw_pattern_1();
void draw_pattern_2();
void clear_screen(uint32_t color);
void swap_buffers();