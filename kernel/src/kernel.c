#include <stdint.h>
#include <stddef.h>
#include <serial/serial.h>
#include <lib/libframebuf.h>

void _kstart(multiboot_info_t *mboot_info)
{
    serial_puts("[AstraOS:Kernel] Starting kernel initialization...\n");
    init_serial();
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    int width = framebuffer->width;
    int height = framebuffer->height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t color = (0xFF000000) |
                ((x * 255 / width) << 16) |
                ((y * 255 / height) << 8) |
                ((x + y) % 255);
            uint32_t *fb = framebuffer->address;
            fb[y * width + x] = color;

        }
    }

    init_libframebuf(framebuffer);
    draw_rect(100, 100, 100, 100, 0xFFFFFF);
    draw_hline(100, 250, 100, 0xFFFFFF);
    draw_vline(100, 300, 100, 0xFFFFFF);

    serial_puts("[AstraOS:Kernel] Starting GDT initialization...");
    init_gdt();
    serial_puts(" OK\n");
    serial_puts("[AstraOS:Kernel] Starting IDT initialization...");
    init_idt();
    init_pic();
    asm("sti");
    serial_puts(" OK\n");
    serial_puts("[AstraOS:Kernel] Kernel has been initialized. Locking up in a while...\n");

    while (1)
    {
        clear();

        draw_roundrect(100, 100, 100, 100, 7, 0xFFFFFF);

        draw_string("Hi, the World!", 110, 110, 0x000000);

        //draw_string("Frames : " + frames, 10, 10, 0xFFFFFF); don't use that lel

        serial_puts("[AstraOS:Kernel] Frames : " + frames + "\n");

        swap_framebuffers();

        frames++;
    }
}
