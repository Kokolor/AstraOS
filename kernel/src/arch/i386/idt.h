#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <lib/lib.h>

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct registers
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

void irq_install_handler(int irq, void (*handler)(struct registers *r));
void irq_uninstall_handler(int irq);
void init_isr();
void init_keyboard();
void init_idt();
void init_irq();