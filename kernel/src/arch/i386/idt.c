#include "idt.h"
#include <lib/lib.h>

struct idt_entry idt[256];
struct idt_ptr idt_pointer;

extern void idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void init_idt()
{
    serial_puts("[AstraOS:Kernel] Initializing IDT...");
    idt_pointer.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_pointer.base = &idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
    serial_puts(" OK\n");
}

/**void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    scancode = inb(0x60);

    if (scancode & 0x80)
    {
        draw_pattern_2();
        swap_buffers();
    }
    else
    {
        draw_pattern_1();
        swap_buffers();
    }
}**/

void init_keyboard()
{
    //irq_install_handler(1, keyboard_handler);
}