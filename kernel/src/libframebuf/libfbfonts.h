#include <stdint.h>

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

extern int cursorx;
extern int cursory;

typedef struct
{
    uint8_t magic[2];
    uint8_t mode;
    uint8_t height;
} font_header_t;

extern uint8_t default_font[];

void draw_char(char, int, int, uint32_t);
void draw_string(char *, int, int, uint32_t);