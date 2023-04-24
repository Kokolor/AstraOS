#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <lib/lib.h>
#include <res/res.h>
#include <libasg/libasg.h>

void task1(void)
{
    char *msg = (char *)0x100; /* le message sera en 0x30100 */
    msg[0] = 't';
    msg[1] = 'a';
    msg[2] = 's';
    msg[3] = 'k';
    msg[4] = '1';
    msg[5] = '\n';
    msg[6] = 0;

    asm("mov %0, %%ebx; mov $0x01, %%eax; int $0x30" ::"m"(msg));
    while (1)
        ;
    return; /* never go there */
}

int _kmain(multiboot_info_t *mboot_info);

void _kstart(multiboot_info_t *mboot_info)
{
    // init_serial();
    set_bootinfo(mboot_info);
    init_idt();
    init_pic();
    init_gdt();
    init_mouse();
    init_libasg(mboot_info);

    asm("sti");

    Color bg = { 255, 0, 0, 0 };
    Color fg = { 255, 255, 255, 255 };
    
    Font f;
    f.charwidth = DEFFONT_CHARWIDTH;
    f.charheight = DEFFONT_CHARHEIGHT;
    f.pixels = deffont;

    int x = 0;
    int y = 0;
    int frame = 0;
    char *frmstr;

    while (1)
    {
        clear_screen(bg);

        itoa(frmstr, frame, 10);

        x = mouse_x_movement;
        y = mouse_y_movement;

        set_pixel(x, y, fg);

        set_string(frmstr, 10, mb_info->framebuffer_height - DEFFONT_CHARHEIGHT - 10, f, fg);

        frame++;

        flush();
    }
    

    /**asm("	movw $0x38, %ax \n \
		ltr %ax");

    asm("   movw $0x18, %ax \n \
                movw %ax, %ss \n \
                movl $0x20000, %esp");

    _kmain(mb_info);**/
}

int _kmain(multiboot_info_t *mboot_info)
{
    memcpy((char *)0x30000, &task1, 100);

    serial_puts("Switching to user task (ring3 mode)\n");

    asm("   cli \n \
		push $0x33 \n \
		push $0x30000 \n \
		pushfl \n \
		popl %%eax \n \
		orl $0x200, %%eax \n \
		and $0xFFFFBFFF, %%eax \n \
		push %%eax \n \
		push $0x23 \n \
		push $0x0 \n \
		movl $0x20000, %0 \n \
		movw $0x2B, %%ax \n \
		movw %%ax, %%ds \n \
		iret"
        : "=m"(default_tss.esp0)
        :);

    serial_puts("Critical error, halting system\n");
    asm("hlt");
}