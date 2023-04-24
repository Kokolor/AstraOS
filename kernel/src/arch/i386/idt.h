#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <lib/lib.h>

#define PS2_DATA_PORT   0x60
#define PS2_STATUS_PORT 0x64

#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x12
#define KEY_E 0x1E
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x18
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C
#define KEY_LSHIFT 0x2A
#define KEY_LALT 0x38
#define KEY_LCTRL 0x1D
#define KEY_SPACE 0x39
#define KEY_CAPSLOCK 0x3A

#define IDTBASE  0x800
#define IDTSIZE  0xFF

#define INTGATE  0x8E00
#define TRAPGATE 0xEF00

struct idt_entry {
	uint16_t offset0_15;
	uint16_t select;
	uint16_t type;
	uint16_t offset16_31;
} __attribute__ ((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

void init_idt(void);
void init_pic(void);

extern int16_t mouse_x_movement;
extern int16_t mouse_y_movement;

void init_mouse();