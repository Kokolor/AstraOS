#include <stdint.h>

typedef struct
{
    uint8_t magic[2];
    uint8_t mode;
    uint8_t height;
} font_header_t;

extern uint8_t font_1[];