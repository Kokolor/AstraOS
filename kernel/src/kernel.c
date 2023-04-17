#include <stdint.h>
#include <stddef.h>
#include <serial/serial.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/idt.h>
#include <limine/limine.h>
#include <lib/libframebuf.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0};

void _start(void)
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
        ;
}

// #include <stdint.h>
// #include <stddef.h>
// #include <serial/serial.h>
// #include <arch/x86_64/gdt.h>
// #include <limine/limine.h>

// static volatile struct limine_framebuffer_request framebuffer_request = {
//     .id = LIMINE_FRAMEBUFFER_REQUEST,
//     .revision = 0};

// void _start(void)
// {
//     init_serial();
//     struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

//     int width = framebuffer->width;
//     int height = framebuffer->height;

//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             uint32_t color = (0xFF000000) |
//                 ((x * 255 / width) << 16) |
//                 ((y * 255 / height) << 8) |
//                 ((x ^ y) % 255);
//             uint32_t *fb = framebuffer->address;
//             fb[y * width + x] = color;

//         }
//     }

//     init_gdt();
//     serial_puts("GDT Loaded.\n");

//     while (1)
//         ;
// }
