#include <lib/lib.h>
#include <arch/i386/gdt.h>

void do_syscalls(int sys_num)
{
	uint16_t ds_select;
	uint32_t ds_base;
	struct gdt_entry *ds;
	unsigned char *message;

	if (sys_num == 1) {
		asm("	mov 44(%%ebp), %%eax	\n \
			mov %%eax, %0		\n \
			mov 24(%%ebp), %%ax	\n \
			mov %%ax, %1" : "=m"(message), "=m"(ds_select) : );

		ds = (struct gdt_entry *) (GDTBASE + (ds_select & 0xF8));
		ds_base = ds->base0_15 + (ds->base16_23 << 16) + (ds->base24_31 << 24);

		serial_puts((char*) (ds_base + message));
	} else {
		serial_puts("syscall\n");
	}

	return;
}