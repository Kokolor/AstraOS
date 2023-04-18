#include <stdint.h>

#define GDTBASE 0x0
#define GDTSIZE 0xFF

struct gdt_descriptor
{
    uint16_t lim0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t acces;
    uint8_t lim16_19 : 4;
    uint8_t other : 4;
    uint8_t base24_31;
} __attribute__((packed));

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_gdt(void);
