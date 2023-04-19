#include <libasg/libasg.h>

multiboot_info_t *mbi;

void init_libasg(multiboot_info_t *info)
{
    mbi = info;
}