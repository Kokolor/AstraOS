#include <stddef.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#define SERIAL_PORT 0x3f8

#define cli asm("cli" ::)
#define sti asm("sti" ::)

#define outb(port, value) \
    asm volatile("outb %%al, %%dx" ::"d"(port), "a"(value));

#define outbp(port, value) \
    asm volatile("outb %%al, %%dx; jmp 1f; 1:" ::"d"(port), "a"(value));

#define inb(port) ({              \
    unsigned char _v;             \
    asm volatile("inb %%dx, %%al" \
                 : "=a"(_v)       \
                 : "d"(port));    \
    _v;                           \
})

void init_serial(void);
bool serial_is_ready(void);
void serial_putc(char c);
void serial_puts(const char *str);
void *memcpy(char *dst, char *src, int n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
unsigned short inw(unsigned short port);
void outw(unsigned short port, unsigned short value);
void delay(uint32_t ms);
void itoa(char *buf, unsigned long int n, int base);
double pow(double base, double exponent);