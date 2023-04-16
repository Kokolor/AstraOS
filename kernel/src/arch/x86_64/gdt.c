#include "gdt.h"

extern void load_gdt(struct gdt_ptr gp);

static struct gdt_entry gdt[3];
static struct gdt_ptr gp;

static void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

void init_gdt()
{
    gp.limit = (sizeof(struct gdt_entry) * 3 - 1);
    gp.base = &gdt;

    gdt_set_entry(0, 0, 0, 0, 0);
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // gp.limit = sizeof(gdt) - 1;
    // gp.base = (uint64_t)&gdt;

    load_gdt(gp);
}