global load_gdt

load_gdt:
    push rbp
    mov rbp, rsp
    lgdt [rbp+16]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp flush

flush:
    pop rbp
    ret
    