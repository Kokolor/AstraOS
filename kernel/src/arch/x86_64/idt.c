#include "idt.h"

static struct idt_ptr idt_pointer;
static struct idt_entry vectors[256];

static void init_idt_entry(struct idt_entry *entry, uint64_t addr, uint8_t attribute)
{
    entry->low = (uint16_t)addr;
    entry->selector = 8;
    entry->attr = attribute;
    entry->mid = (uint16_t)(addr >> 16);
    entry->high = (uint32_t)(addr >> 32);
}

void init_idt(void)
{
    init_idt_entry(&vectors[0], (uint64_t)vector0, 0x8e);
    init_idt_entry(&vectors[1], (uint64_t)vector1, 0x8e);
    init_idt_entry(&vectors[2], (uint64_t)vector2, 0x8e);
    init_idt_entry(&vectors[3], (uint64_t)vector3, 0x8e);
    init_idt_entry(&vectors[4], (uint64_t)vector4, 0x8e);
    init_idt_entry(&vectors[5], (uint64_t)vector5, 0x8e);
    init_idt_entry(&vectors[6], (uint64_t)vector6, 0x8e);
    init_idt_entry(&vectors[7], (uint64_t)vector7, 0x8e);
    init_idt_entry(&vectors[8], (uint64_t)vector8, 0x8e);
    init_idt_entry(&vectors[10], (uint64_t)vector10, 0x8e);
    init_idt_entry(&vectors[11], (uint64_t)vector11, 0x8e);
    init_idt_entry(&vectors[12], (uint64_t)vector12, 0x8e);
    init_idt_entry(&vectors[13], (uint64_t)vector13, 0x8e);
    init_idt_entry(&vectors[14], (uint64_t)vector14, 0x8e);
    init_idt_entry(&vectors[16], (uint64_t)vector16, 0x8e);
    init_idt_entry(&vectors[17], (uint64_t)vector17, 0x8e);
    init_idt_entry(&vectors[18], (uint64_t)vector18, 0x8e);
    init_idt_entry(&vectors[19], (uint64_t)vector19, 0x8e);
    init_idt_entry(&vectors[32], (uint64_t)vector32, 0x8e);
    init_idt_entry(&vectors[39], (uint64_t)vector39, 0x8e);

    idt_pointer.limit = sizeof(vectors) - 1;
    idt_pointer.addr = (uint64_t)vectors;
    load_idt(&idt_pointer);
}

void keyboard_handler(struct regs *tf)
{
    struct keyboard_regs *regs = (struct keyboard_regs *)tf;
    unsigned char scancode = regs->scancode;

    serial_puts("BF");

    eoi();
}

void double_fault_handler(struct idt_error_code *tf)
{
    serial_puts("DOUBLE FAULT!");

    while (1)
    {
    }
}

void gp_fault_handler(struct idt_error_code *tf)
{
    serial_puts("GENERAL PROTECTION FAULT!");

    while (1)
    {
    }
}

void handler(struct regs *tf)
{
    unsigned char isr_value;

    switch (tf->trapno)
    {
    case 32:
        eoi();
        break;

    case 33:
        keyboard_handler(tf);
        break;

    case 39:
        isr_value = read_isr();
        if ((isr_value & (1 << 7)) != 0)
        {
            eoi();
        }
        break;

    case 8:
        double_fault_handler((struct idt_error_code *)tf);
        break;

    case 13:
        gp_fault_handler((struct idt_error_code *)tf);
        break;

    default:
        while (1)
        {
        }
    }
}

void init_pic(void) {
        uint8_t A1, A2;

        A1 = inb(PIC1_DATA);
        A2 = inb(PIC2_DATA);

        outb(PIC1_COMMAND, ICW1);
        outb(PIC2_COMMAND, ICW1);

        outb(PIC1_DATA, 0x20);
        outb(PIC2_DATA, 0x28);

        outb(PIC1_DATA, 4);
        outb(PIC2_DATA, 2);

        outb(PIC1_DATA, ICW4_8086);
        outb(PIC2_DATA, ICW4_8086);

        outb(PIC1_DATA, A1);
        outb(PIC2_DATA, A2);
    }