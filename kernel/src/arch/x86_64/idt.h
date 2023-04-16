#include <stdint.h>

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20

#define ICW1 0x11
#define ICW4_8086 0x01

struct idt_entry
{
    uint16_t low;
    uint16_t selector;
    uint8_t res0;
    uint8_t attr;
    uint16_t mid;
    uint32_t high;
    uint32_t res1;
};

struct idt_ptr
{
    uint16_t limit;
    uint64_t addr;
} __attribute__((packed));

struct idt_error_code
{
    uint64_t code;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

struct keyboard_regs
{
    uint8_t scancode;
    uint8_t _pad;
    uint16_t _pad2;
};

struct regs
{
    int64_t r15;
    int64_t r14;
    int64_t r13;
    int64_t r12;
    int64_t r11;
    int64_t r10;
    int64_t r9;
    int64_t r8;
    int64_t rbp;
    int64_t rdi;
    int64_t rsi;
    int64_t rdx;
    int64_t rcx;
    int64_t rbx;
    int64_t rax;
    int64_t trapno;
    int64_t errorcode;
    int64_t rip;
    int64_t cs;
    int64_t rflags;
    int64_t rsp;
    int64_t ss;
};

void vector0(void);
void vector1(void);
void vector2(void);
void vector3(void);
void vector4(void);
void vector5(void);
void vector6(void);
void vector7(void);
void vector8(void);
void vector10(void);
void vector11(void);
void vector12(void);
void vector13(void);
void vector14(void);
void vector16(void);
void vector17(void);
void vector18(void);
void vector19(void);
void vector32(void);
void vector39(void);
void init_idt(void);
void eoi(void);
void load_idt(struct idt_pointer *ptr);
unsigned char read_isr(void);

void init_idt(void);
void init_pic();