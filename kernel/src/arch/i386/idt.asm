extern vector0_handler, vector13_handler, vector32_handler, vector33_handler, do_syscalls
global vector0, vector13, vector32, vector33, vector48

%macro	SAVE_REGS 0
	pushad 
	push ds
	push es
	push fs
	push gs 
	push ebx
	mov bx,0x10
	mov ds,bx
	pop ebx
%endmacro

%macro	RESTORE_REGS 0
	pop gs
	pop fs
	pop es
	pop ds
	popad
%endmacro

vector0:
	SAVE_REGS
	call vector0_handler
	mov al,0x20
	out 0x20,al
	RESTORE_REGS
	iret

vector13:
	SAVE_REGS
	call vector13_handler
	RESTORE_REGS
	add esp,4
	iret

vector32:
	SAVE_REGS
	call vector32_handler
	mov al,0x20
	out 0x20,al
	RESTORE_REGS
	iret

vector33:
	SAVE_REGS
	call vector33_handler
	mov al,0x20
	out 0x20,al
	RESTORE_REGS
	iret

vector48:
	SAVE_REGS
	push eax
	call do_syscalls
	pop eax
	RESTORE_REGS
	iret
