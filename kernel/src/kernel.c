#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <lib/lib.h>
#include <res/res.h>
#include <libasg/libasg.h>
#include <rmusr/rmusr.h>

void task1()
{
    /*char *msg = (char *)0x100;
    msg[0] = 't';
    msg[1] = 'a';
    msg[2] = 's';
    msg[3] = 'k';
    msg[4] = '1';
    msg[5] = '\n';
    msg[6] = 0;

    asm("mov %0, %%ebx; mov $0x01, %%eax; int $0x30" ::"m"(msg));*/

    
    Color c = { 255, 0, 164, 0 };
    Color c2 = { 255, 255, 255, 255 };

    Font f;
    f.charwidth = DEFFONT_CHARWIDTH;
    f.charheight = DEFFONT_CHARHEIGHT;
    f.pixels = deffont;

    Image *e;
    e->width = SUCC_WIDTH;
    e->height = SUCC_HEIGHT;
    e->pixels = (uint32_t *)succ;

    set_rect(0, 0, mb_info->framebuffer_width, mb_info->framebuffer_height, c);

    set_string("Hello, User Space!", 10, 10, f, c2);

    flush();

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
    init_libasg(mboot_info);

    //asm("	movw $0x38, %ax \n \
		ltr %ax");

    //asm("   movw $0x18, %ax \n \
                movw %ax, %ss \n \
                movl $0x20000, %esp");

    _kmain(mb_info);
}

int _kmain(multiboot_info_t *mboot_info)
{
    //memcpy((char *)0x30000, &task1, 100);

    serial_puts("[AstraOS:Kernel] Switching to user task (ring3 mode)...");
    
    /**
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
<<<<<<< HEAD
        :);**/
    
    init_usr(&task1);
    
    serial_puts(" FAIL\n");
    serial_puts("[AstraOS:Kernel] Critical error, halting system.\n");
=======
        :);

    serial_puts("Critical error, halting system\n");
>>>>>>> 050584b6e49b06f17dba9c9388bd0531f3b7294f
    asm("hlt");
}