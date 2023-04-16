#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#define SERIAL_PORT 0x3f8

void init_serial(void);
void serial_putc(char c);
void serial_puts(const char *str);