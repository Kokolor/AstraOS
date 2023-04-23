#include <rmusr/rmusr.h>

void init_usr(void (*function)())
{
    asm volatile("movl %%esp, %%eax\n\t"
                 "movl %[stack_top], %%esp\n\t"
                 "pushl %[cs]\n\t"
                 "pushl %[entry]\n\t"
                 "pushfl\n\t" 
                 "pushl %[ss]\n\t"
                 "pushl %[stack_top]\n\t"
                 "iret\n\t"
                 :
                 : [entry] "r" (function),
                   [cs]    "i" (0x08),  /* User code segment selector */
                   [ss]    "i" (0x10),  /* User stack segment selector */
                   [stack_top] "r" (0x400000)
                 : "eax", "memory");
}