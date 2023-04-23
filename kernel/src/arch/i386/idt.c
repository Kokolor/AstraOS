#include <lib/lib.h>
#include <libasg/libasg.h>
#include <res/res.h>
#include <multiboot/boot_info.h>
#include "idt.h"

void vector0(void);
void vector13(void);
void vector32(void);
void vector33(void);
void vector48(void);

extern int get_eip();

struct idt_ptr idt_pointer;
struct idt_entry idt[IDTSIZE];

void idt_set_gate(uint16_t select, uint32_t offset, uint16_t type, struct idt_entry *descriptor)
{
    descriptor->offset0_15 = (offset & 0xffff);
    descriptor->select = select;
    descriptor->type = type;
    descriptor->offset16_31 = (offset & 0xffff0000) >> 16;
    return;
}

void init_idt(void)
{
    serial_puts("[AstraOS:Kernel] Initializing IDT...");
    int i;

    for (i = 0; i < IDTSIZE; i++)
        idt_set_gate(0x08, (uint32_t)vector0, INTGATE, &idt[i]);

    idt_set_gate(0x08, (uint32_t)vector13, INTGATE, &idt[13]);

    idt_set_gate(0x08, (uint32_t)vector32, INTGATE, &idt[32]);
    idt_set_gate(0x08, (uint32_t)vector33, INTGATE, &idt[33]);

    idt_set_gate(0x08, (uint32_t)vector48, TRAPGATE, &idt[48]);

    idt_pointer.limit = IDTSIZE * 8;
    idt_pointer.base = IDTBASE;

    memcpy((char *)idt_pointer.base, (char *)idt, idt_pointer.limit);

    asm("lidtl (idt_pointer)");

    serial_puts(" OK\n");
}
void init_pic(void)
{
    serial_puts("[AstraOS:Kernel] Initializing PIC...");

    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x70);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    serial_puts(" OK\n");
}

unsigned char keyboard_map[] = {
    0x1B, 0x1B, 0x1B, 0x1B, /*      esc     (0x01)  */
    '1', '!', '1', '1',
    '2', '@', '2', '2',
    '3', '#', '3', '3',
    '4', '$', '4', '4',
    '5', '%', '5', '5',
    '6', '^', '6', '6',
    '7', '&', '7', '7',
    '8', '*', '8', '8',
    '9', '(', '9', '9',
    '0', ')', '0', '0',
    '-', '_', '-', '-',
    '=', '+', '=', '=',
    0x08, 0x08, 0x7F, 0x08, /*      backspace       */
    0x09, 0x09, 0x09, 0x09, /*      tab     */
    'q', 'Q', 'q', 'q',
    'w', 'W', 'w', 'w',
    'e', 'E', 'e', 'e',
    'r', 'R', 'r', 'r',
    't', 'T', 't', 't',
    'y', 'Y', 'y', 'y',
    'u', 'U', 'u', 'u',
    'i', 'I', 'i', 'i',
    'o', 'O', 'o', 'o',
    'p', 'P', 'p', 'p',
    '[', '{', '[', '[',
    ']', '}', ']', ']',
    0x0A, 0x0A, 0x0A, 0x0A, /*      enter   */
    0xFF, 0xFF, 0xFF, 0xFF, /*      ctrl    */
    'a', 'A', 'a', 'a',
    's', 'S', 's', 's',
    'd', 'D', 'd', 'd',
    'f', 'F', 'f', 'f',
    'g', 'G', 'g', 'g',
    'h', 'H', 'h', 'h',
    'j', 'J', 'j', 'j',
    'k', 'K', 'k', 'k',
    'l', 'L', 'l', 'l',
    ';', ':', ';', ';',
    0x27, 0x22, 0x27, 0x27, /*      '"      */
    '`', '~', '`', '`',     /*      `~      */
    0xFF, 0xFF, 0xFF, 0xFF, /*      Lshift  (0x2a)  */
    '\\', '|', '\\', '\\',
    'z', 'Z', 'z', 'z',
    'x', 'X', 'x', 'x',
    'c', 'C', 'c', 'c',
    'v', 'V', 'v', 'v',
    'b', 'B', 'b', 'b',
    'n', 'N', 'n', 'n',
    'm', 'M', 'm', 'm',
    0x2C, 0x3C, 0x2C, 0x2C, /*      ,<      */
    0x2E, 0x3E, 0x2E, 0x2E, /*      .>      */
    0x2F, 0x3F, 0x2F, 0x2F, /*      /?      */
    0xFF, 0xFF, 0xFF, 0xFF, /*      Rshift  (0x36)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x37)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x38)  */
    ' ', ' ', ' ', ' ',     /*      space   */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x3a)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x3b)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x3c)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x3d)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x3e)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x3f)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x40)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x41)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x42)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x43)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x44)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x45)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x46)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x47)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x48)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x49)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x4a)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x4b)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x4c)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x4d)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x4e)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x4f)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x50)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x51)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x52)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x53)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x54)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x55)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x56)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x57)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x58)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x59)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x5a)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x5b)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x5c)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x5d)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x5e)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x5f)  */
    0xFF, 0xFF, 0xFF, 0xFF, /*      (0x60)  */
    0xFF, 0xFF, 0xFF, 0xFF  /*      (0x61)  */
};

void vector0_handler(void)
{
}

void vector13_handler(void)
{
    serial_puts(" Kernel panic. Message : GPF\n");
    
    Color c = { 255, 164, 0, 0 };
    Color c2 = { 255, 255, 255, 255 };

    Font f;
    f.charwidth = DEFFONT_CHARWIDTH;
    f.charheight = DEFFONT_CHARHEIGHT;
    f.pixels = deffont;
    
    set_rect(0, 0, mb_info->framebuffer_width, mb_info->framebuffer_height, c);

    Position pcursor = set_string("AstraOS ran into a problem. (also called kernel panic).\n\nHere's some debug info : \nMessage : General Protection Fault.\nLast Known Address : ", 10, 10, f, c2);

    char *lka;

    itoa(lka, get_eip(), 10);
    
    set_string(lka, pcursor.x, pcursor.y, f, c2);

    serial_puts("Last Known Address : ");
    serial_puts(lka);
    serial_putc('\n');

    //set_image(e, /**mb_info->framebuffer_width / 2 - ERROR_WIDTH / 2, mb_info->framebuffer_height / 2 - ERROR_HEIGHT / 2**/100, 100);

    flush();
    while (1)
        ;
}

void vector32_handler(void)
{
    static int tic = 0;
    static int sec = 0;
    tic++;
    if (tic % 100 == 0)
    {
        sec++;
        tic = 0;
        serial_putc('.');
    }
}

void vector33_handler(void)
{
    unsigned char i;
    static int lshift_enable;
    static int rshift_enable;
    static int alt_enable;
    static int ctrl_enable;

    do
    {
        i = inb(0x64);
    } while ((i & 0x01) == 0);

    i = inb(0x60);
    i--;

    if (i < 0x80)
    {
        switch (i)
        {
        case 0x29:
            lshift_enable = 1;
            break;
        case 0x35:
            rshift_enable = 1;
            break;
        case 0x1C:
            ctrl_enable = 1;
            break;
        case 0x37:
            alt_enable = 1;
            break;
        default:
            serial_putc(keyboard_map
                            [i * 4 + (lshift_enable || rshift_enable)]);
        }
    }
    else
    {
        i -= 0x80;
        switch (i)
        {
        case 0x29:
            lshift_enable = 0;
            break;
        case 0x35:
            rshift_enable = 0;
            break;
        case 0x1C:
            ctrl_enable = 0;
            break;
        case 0x37:
            alt_enable = 0;
            break;
        }
    }
}