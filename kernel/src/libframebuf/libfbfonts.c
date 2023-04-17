#include <libframebuf/libframebuf.h>
#include <libframebuf/libfbfonts.h>

int cursorx = 0;
int cursory = 0;

uint8_t default_font[] = {
  0x36, 0x04, 0x02, 0x10, 0x00, 0x00, 0x7e, 0xc3, 0x99, 0x99, 0xf3, 0xe7,
  0xe7, 0xff, 0xe7, 0xe7, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7f, 0xe6, 0x66, 0x66, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x06, 0x0c, 0xfe, 0x18, 0x30, 0xfe, 0x60, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x60, 0x30,
  0x18, 0x0c, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
  0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe,
  0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xe0, 0x62,
  0x66, 0x6c, 0x18, 0x30, 0x66, 0xce, 0x96, 0x3f, 0x06, 0x06, 0x00, 0x00,
  0x00, 0x60, 0xe0, 0x62, 0x66, 0x6c, 0x18, 0x30, 0x60, 0xce, 0x9b, 0x06,
  0x0c, 0x1f, 0x00, 0x00, 0x00, 0xe0, 0x30, 0x62, 0x36, 0xec, 0x18, 0x30,
  0x66, 0xce, 0x96, 0x3f, 0x06, 0x06, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x06, 0x7c, 0x00, 0x00, 0x00, 0x0e, 0x1b,
  0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0xd8, 0x70, 0x00,
  0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18,
  0x7e, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xc2, 0xc6, 0x0c, 0x18, 0x30, 0x60, 0xdb, 0x9b, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xf1, 0x5b, 0x55, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xdb, 0xdb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0c, 0x18, 0x30, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x33, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66,
  0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66,
  0x66, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x66, 0x66, 0x66, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x0c, 0x00, 0x00,
  0x6c, 0x38, 0x00, 0x3c, 0x66, 0xc2, 0xc0, 0xde, 0xc6, 0xc6, 0x66, 0x3a,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0x00, 0x76, 0xcc, 0xcc,
  0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xcc, 0x78, 0x00, 0x00, 0x18, 0x18, 0x00,
  0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0x60, 0x38, 0x0c,
  0x06, 0xc6, 0xc6, 0x7c, 0x0c, 0x06, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7c, 0xc6, 0x60, 0x38, 0x0c, 0xc6, 0x7c, 0x0c, 0x06, 0x7c, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x3c, 0x18, 0x18,
  0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66,
  0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x6c, 0x6c, 0xfe, 0x6c, 0x6c, 0x6c, 0xfe, 0x6c, 0x6c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x7c, 0xd6, 0xd2, 0xd0, 0x7c,
  0x16, 0x96, 0xd6, 0x7c, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xc2, 0xc6, 0x0c, 0x18, 0x30, 0x60, 0xc6, 0x86, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x38, 0x6c, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0xcc, 0xcc, 0x76,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0xfe,
  0x38, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18,
  0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xd6, 0xd6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38,
  0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7c, 0xc6, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xc6, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x06, 0x06, 0x3c, 0x06,
  0x06, 0x06, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1c,
  0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x0c, 0x0c, 0x1e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0xc0, 0xc0, 0xc0, 0xfc, 0x06, 0x06, 0x06, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x60, 0xc0, 0xc0, 0xfc, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xc6,
  0x06, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0x7e, 0x06,
  0x06, 0x06, 0x0c, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18,
  0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60,
  0x30, 0x18, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0x0c, 0x18, 0x18,
  0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6,
  0xc6, 0xc6, 0xde, 0xde, 0xde, 0xdc, 0xc0, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0xc6,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x66, 0x66, 0x66, 0x7c, 0x66,
  0x66, 0x66, 0x66, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x66,
  0xc2, 0xc0, 0xc0, 0xc0, 0xc0, 0xc2, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6c, 0xf8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x66, 0x62, 0x68, 0x78, 0x68,
  0x60, 0x62, 0x66, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x66,
  0x62, 0x68, 0x78, 0x68, 0x60, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3c, 0x66, 0xc2, 0xc0, 0xc0, 0xde, 0xc6, 0xc6, 0x66, 0x3a,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6,
  0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0xcc, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0x66, 0x66, 0x6c, 0x78, 0x78,
  0x6c, 0x66, 0x66, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x60,
  0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xe6, 0xf6, 0xfe, 0xde, 0xce,
  0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6,
  0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfc, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0x60, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6,
  0xc6, 0xd6, 0xde, 0x7c, 0x0c, 0x0e, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x66,
  0x66, 0x66, 0x7c, 0x6c, 0x66, 0x66, 0x66, 0xe6, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7c, 0xc6, 0xc6, 0x60, 0x38, 0x0c, 0x06, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xdb, 0x99, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb,
  0xdb, 0xff, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xc3,
  0x66, 0x3c, 0x18, 0x18, 0x3c, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc3, 0x86, 0x0c, 0x18, 0x30,
  0x60, 0xc1, 0xc3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
  0x0c, 0x0c, 0x0c, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xfe, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x0c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x78, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x60, 0x60, 0x78, 0x6c, 0x66, 0x66, 0x66, 0x66, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0,
  0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x0c,
  0x0c, 0x3c, 0x6c, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0xc0, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x64, 0x60, 0xf0, 0x60,
  0x60, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xcc, 0x78, 0x00,
  0x00, 0x00, 0xe0, 0x60, 0x60, 0x6c, 0x76, 0x66, 0x66, 0x66, 0x66, 0xe6,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06,
  0x00, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3c, 0x00,
  0x00, 0x00, 0xe0, 0x60, 0x60, 0x66, 0x6c, 0x78, 0x78, 0x6c, 0x66, 0xe6,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xe6, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xdc, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x7c,
  0x0c, 0x0c, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x76, 0x66,
  0x60, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7c, 0xc6, 0x60, 0x38, 0x0c, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x30, 0x36, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0xcc,
  0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xff, 0x66,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c,
  0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7e, 0x06, 0x0c, 0xf8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xcc, 0x18, 0x30, 0x60, 0xc6, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x18, 0x18, 0x18, 0x70, 0x18,
  0x18, 0x18, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0e, 0x18, 0x18, 0x18, 0x18, 0x70,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x60, 0x30, 0x18, 0x00, 0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00, 0x38, 0x6c, 0xc6, 0xc6,
  0xfe, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0x00,
  0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x76, 0xdc, 0x00, 0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0x38, 0x6c, 0xc6, 0xc6,
  0xfe, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x38, 0x10,
  0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0x6d, 0xcc, 0xcc, 0xff, 0xcc, 0xcc, 0xcc, 0xcd, 0xcf,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0xc2, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc2, 0x66, 0x3c, 0x0c, 0x06, 0x7c, 0x00, 0x60, 0x30, 0x18, 0x00,
  0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0x62, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x0c, 0x18, 0x30, 0x00, 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0x62, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0x00, 0xfe, 0x62, 0x68, 0x78,
  0x68, 0x60, 0x62, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00,
  0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0x62, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x18, 0x0c, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00, 0x3c, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0x00,
  0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x66, 0x66, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x6c, 0x66, 0x66, 0xf6, 0x66,
  0x66, 0x66, 0x6c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x76, 0xdc, 0x00, 0xc6,
  0xe6, 0xf6, 0xfe, 0xde, 0xce, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00,
  0x60, 0x30, 0x18, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00, 0x7c, 0xc6, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0x00,
  0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x76, 0xdc, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0x7c, 0xc6, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3d, 0x67, 0x66, 0x6e, 0x7e, 0x76, 0x66, 0x66, 0xe6, 0xbc,
  0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x00, 0xc6, 0xc6, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00,
  0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x38, 0x6c, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0xc6, 0xc6, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00,
  0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xf0, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x60, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0xd8, 0xcc,
  0xc6, 0xc6, 0xc6, 0xcc, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x55, 0xaa, 0x55,
  0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55,
  0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x3c, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x7c, 0xd6, 0xd0,
  0xd0, 0xd0, 0xd6, 0x7c, 0x10, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x64,
  0x60, 0x60, 0xf0, 0x60, 0x60, 0x60, 0x66, 0xfc, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1e, 0x33, 0x60, 0xfc, 0x60, 0xf8, 0x60, 0x60, 0x33, 0x1e,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x7e,
  0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0x10, 0x7c,
  0xc6, 0xc6, 0x60, 0x38, 0x0c, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7c, 0xc6, 0x60, 0x38, 0x6c, 0xc6, 0xc6, 0x6c, 0x38, 0x0c, 0xc6,
  0x7c, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0x10, 0x00, 0x7c, 0xc6, 0x60,
  0x38, 0x0c, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42,
  0x99, 0xa5, 0xa1, 0xa1, 0xa5, 0x99, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x3c, 0x6c, 0x6c, 0x3e, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x6c, 0xd8,
  0x6c, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x66, 0x3c, 0x66, 0x66, 0x66, 0x3c, 0x66, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42,
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7e,
  0x18, 0x18, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x18,
  0x30, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x78, 0x0c, 0x38, 0x0c, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0x10, 0xff, 0xc3, 0x86, 0x0c, 0x18,
  0x30, 0x61, 0xc3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7b, 0x60, 0x60, 0xc0, 0x00,
  0x00, 0x00, 0x7f, 0xdb, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0x10,
  0x00, 0xfe, 0xcc, 0x18, 0x30, 0x60, 0xc6, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0x38, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x6c, 0x6c, 0x38, 0x00, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xd8, 0x6c, 0x36, 0x6c, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7f, 0xcd, 0xcc, 0xcc, 0xcf, 0xcc, 0xcc, 0xcc, 0xcd, 0x7f,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xdb, 0xdb,
  0xdf, 0xd8, 0xdb, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x00,
  0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x30, 0x60, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22,
  0x88, 0x22, 0x88, 0x22, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
  0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x30,
  0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x06, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
  0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x3f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x06,
  0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36,
  0x36, 0x36, 0x37, 0x30, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
  0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x06, 0xf6, 0x36, 0x36, 0x36,
  0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
  0xf7, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
  0x36, 0x36, 0xf7, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xf7, 0x00, 0xf7, 0x36, 0x36, 0x36,
  0x36, 0x36, 0x36, 0x36, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x18, 0x3c,
  0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x30, 0x7f,
  0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0x0c, 0xfe, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x30, 0x18, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00, 0x78, 0x0c, 0x7c,
  0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c,
  0x00, 0x78, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x76, 0xdc, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0x78, 0x0c, 0x7c,
  0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x38,
  0x00, 0x78, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x1b, 0x7b, 0xdf, 0xd8, 0xdb, 0x6e,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0,
  0xc0, 0xc0, 0xc6, 0x7c, 0x0c, 0x06, 0x7c, 0x00, 0x00, 0x60, 0x30, 0x18,
  0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0c, 0x18, 0x30, 0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0xc0, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0x00, 0x7c, 0xc6, 0xfe,
  0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c,
  0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x30, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00, 0x38, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c,
  0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x6c, 0x6c, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x18, 0x2c, 0x06, 0x3e, 0x66,
  0x66, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xdc,
  0x00, 0xdc, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x30, 0x18, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x00, 0x7c, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c,
  0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x76, 0xdc, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0x7c, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x18, 0x00, 0x7e, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x67, 0x6e, 0x7e, 0x76, 0xe6, 0xbc,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x00, 0xcc, 0xcc, 0xcc,
  0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30,
  0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x38, 0x6c, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x76,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0xcc, 0xcc, 0xcc,
  0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30,
  0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7e, 0x06, 0x0c, 0xf8, 0x00,
  0x00, 0x00, 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7c,
  0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x00, 0xc6, 0xc6, 0xc6,
  0xc6, 0xc6, 0xc6, 0x7e, 0x06, 0x0c, 0xf8, 0x00, 0xfd, 0xff, 0xff, 0xff,
  0xc0, 0x03, 0xff, 0xff, 0x60, 0x22, 0xff, 0xff, 0x64, 0x22, 0xff, 0xff,
  0x65, 0x22, 0xff, 0xff, 0xa0, 0x25, 0xac, 0x25, 0xae, 0x25, 0xfc, 0x25,
  0xfe, 0x25, 0x1b, 0x2b, 0x0e, 0x22, 0xff, 0xff, 0xc6, 0x25, 0x66, 0x26,
  0x25, 0x2b, 0x27, 0x2b, 0xff, 0xff, 0xbc, 0x00, 0xff, 0xff, 0xbd, 0x00,
  0xff, 0xff, 0xbe, 0x00, 0xff, 0xff, 0xa6, 0x00, 0xff, 0xff, 0xa8, 0x00,
  0xff, 0xff, 0xb8, 0x00, 0xff, 0xff, 0x92, 0x01, 0xff, 0xff, 0x20, 0x20,
  0xff, 0xff, 0x21, 0x20, 0xff, 0xff, 0x30, 0x20, 0xff, 0xff, 0x22, 0x21,
  0xff, 0xff, 0x26, 0x20, 0xff, 0xff, 0x39, 0x20, 0xff, 0xff, 0x3a, 0x20,
  0xff, 0xff, 0x1c, 0x20, 0x1f, 0x20, 0x36, 0x20, 0xff, 0xff, 0x1d, 0x20,
  0xba, 0x02, 0xdd, 0x02, 0xee, 0x02, 0x33, 0x20, 0xff, 0xff, 0x1e, 0x20,
  0xff, 0xff, 0x42, 0x2e, 0xff, 0xff, 0x41, 0x2e, 0xce, 0x02, 0xff, 0xff,
  0x1e, 0x01, 0xff, 0xff, 0x1f, 0x01, 0xff, 0xff, 0x30, 0x01, 0xff, 0xff,
  0x31, 0x01, 0xff, 0xff, 0x5e, 0x01, 0xff, 0xff, 0x5f, 0x01, 0xff, 0xff,
  0x20, 0x00, 0xa0, 0x00, 0x00, 0x20, 0x01, 0x20, 0x02, 0x20, 0x03, 0x20,
  0x04, 0x20, 0x05, 0x20, 0x06, 0x20, 0x07, 0x20, 0x08, 0x20, 0x09, 0x20,
  0x0a, 0x20, 0x2f, 0x20, 0x5f, 0x20, 0xff, 0xff, 0x21, 0x00, 0xff, 0xff,
  0x22, 0x00, 0xff, 0xff, 0x23, 0x00, 0xff, 0xff, 0x24, 0x00, 0xff, 0xff,
  0x25, 0x00, 0xff, 0xff, 0x26, 0x00, 0xff, 0xff, 0x27, 0x00, 0xb4, 0x00,
  0xb9, 0x02, 0xbc, 0x02, 0xca, 0x02, 0x19, 0x20, 0x32, 0x20, 0xff, 0xff,
  0x28, 0x00, 0xff, 0xff, 0x29, 0x00, 0xff, 0xff, 0x2a, 0x00, 0x4e, 0x20,
  0x17, 0x22, 0xff, 0xff, 0x2b, 0x00, 0xff, 0xff, 0x2c, 0x00, 0xcf, 0x02,
  0x1a, 0x20, 0xff, 0xff, 0x2d, 0x00, 0xad, 0x00, 0x10, 0x20, 0x11, 0x20,
  0x12, 0x20, 0x13, 0x20, 0x43, 0x20, 0x12, 0x22, 0xff, 0xff, 0x2e, 0x00,
  0x24, 0x20, 0xff, 0xff, 0x2f, 0x00, 0x44, 0x20, 0x15, 0x22, 0xff, 0xff,
  0x30, 0x00, 0xff, 0xff, 0x31, 0x00, 0xff, 0xff, 0x32, 0x00, 0xff, 0xff,
  0x33, 0x00, 0xff, 0xff, 0x34, 0x00, 0xff, 0xff, 0x35, 0x00, 0xff, 0xff,
  0x36, 0x00, 0xff, 0xff, 0x37, 0x00, 0xff, 0xff, 0x38, 0x00, 0xff, 0xff,
  0x39, 0x00, 0xff, 0xff, 0x3a, 0x00, 0x36, 0x22, 0xff, 0xff, 0x3b, 0x00,
  0xff, 0xff, 0x3c, 0x00, 0xff, 0xff, 0x3d, 0x00, 0x40, 0x2e, 0xff, 0xff,
  0x3e, 0x00, 0xff, 0xff, 0x3f, 0x00, 0xff, 0xff, 0x40, 0x00, 0xff, 0xff,
  0x41, 0x00, 0xff, 0xff, 0x42, 0x00, 0xff, 0xff, 0x43, 0x00, 0xff, 0xff,
  0x44, 0x00, 0xff, 0xff, 0x45, 0x00, 0xff, 0xff, 0x46, 0x00, 0xff, 0xff,
  0x47, 0x00, 0xff, 0xff, 0x48, 0x00, 0xff, 0xff, 0x49, 0x00, 0xff, 0xff,
  0x4a, 0x00, 0xff, 0xff, 0x4b, 0x00, 0x2a, 0x21, 0xff, 0xff, 0x4c, 0x00,
  0xff, 0xff, 0x4d, 0x00, 0xff, 0xff, 0x4e, 0x00, 0xff, 0xff, 0x4f, 0x00,
  0xff, 0xff, 0x50, 0x00, 0xff, 0xff, 0x51, 0x00, 0xff, 0xff, 0x52, 0x00,
  0xff, 0xff, 0x53, 0x00, 0xff, 0xff, 0x54, 0x00, 0xff, 0xff, 0x55, 0x00,
  0xff, 0xff, 0x56, 0x00, 0xff, 0xff, 0x57, 0x00, 0xff, 0xff, 0x58, 0x00,
  0xff, 0xff, 0x59, 0x00, 0xff, 0xff, 0x5a, 0x00, 0xff, 0xff, 0x5b, 0x00,
  0xff, 0xff, 0x5c, 0x00, 0xf5, 0x29, 0xff, 0xff, 0x5d, 0x00, 0xff, 0xff,
  0x5e, 0x00, 0xc4, 0x02, 0xc6, 0x02, 0x03, 0x23, 0xff, 0xff, 0x5f, 0x00,
  0xff, 0xff, 0x60, 0x00, 0xbb, 0x02, 0xbd, 0x02, 0xcb, 0x02, 0x18, 0x20,
  0x1b, 0x20, 0x35, 0x20, 0xff, 0xff, 0x61, 0x00, 0xff, 0xff, 0x62, 0x00,
  0xff, 0xff, 0x63, 0x00, 0xff, 0xff, 0x64, 0x00, 0xff, 0xff, 0x65, 0x00,
  0xff, 0xff, 0x66, 0x00, 0xff, 0xff, 0x67, 0x00, 0xff, 0xff, 0x68, 0x00,
  0xff, 0xff, 0x69, 0x00, 0xff, 0xff, 0x6a, 0x00, 0xff, 0xff, 0x6b, 0x00,
  0xff, 0xff, 0x6c, 0x00, 0xff, 0xff, 0x6d, 0x00, 0xff, 0xff, 0x6e, 0x00,
  0xff, 0xff, 0x6f, 0x00, 0xff, 0xff, 0x70, 0x00, 0xff, 0xff, 0x71, 0x00,
  0xff, 0xff, 0x72, 0x00, 0xff, 0xff, 0x73, 0x00, 0xff, 0xff, 0x74, 0x00,
  0xff, 0xff, 0x75, 0x00, 0xff, 0xff, 0x76, 0x00, 0xff, 0xff, 0x77, 0x00,
  0xff, 0xff, 0x78, 0x00, 0xff, 0xff, 0x79, 0x00, 0xff, 0xff, 0x7a, 0x00,
  0xff, 0xff, 0x7b, 0x00, 0xff, 0xff, 0x7c, 0x00, 0x23, 0x22, 0xff, 0xff,
  0x7d, 0x00, 0xff, 0xff, 0x7e, 0x00, 0xdc, 0x02, 0xff, 0xff, 0x22, 0x20,
  0x19, 0x22, 0xcf, 0x25, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xc1, 0x00,
  0xff, 0xff, 0xc2, 0x00, 0xff, 0xff, 0xc3, 0x00, 0xff, 0xff, 0xc4, 0x00,
  0xff, 0xff, 0xc5, 0x00, 0x2b, 0x21, 0xff, 0xff, 0xc6, 0x00, 0xff, 0xff,
  0xc7, 0x00, 0xff, 0xff, 0xc8, 0x00, 0xff, 0xff, 0xc9, 0x00, 0xff, 0xff,
  0xca, 0x00, 0xff, 0xff, 0xcb, 0x00, 0xff, 0xff, 0xcc, 0x00, 0xff, 0xff,
  0xcd, 0x00, 0xff, 0xff, 0xce, 0x00, 0xff, 0xff, 0xcf, 0x00, 0xff, 0xff,
  0xd0, 0x00, 0x10, 0x01, 0xff, 0xff, 0xd1, 0x00, 0xff, 0xff, 0xd2, 0x00,
  0xff, 0xff, 0xd3, 0x00, 0xff, 0xff, 0xd4, 0x00, 0xff, 0xff, 0xd5, 0x00,
  0xff, 0xff, 0xd6, 0x00, 0xff, 0xff, 0xd7, 0x00, 0xff, 0xff, 0xd8, 0x00,
  0xff, 0xff, 0xd9, 0x00, 0xff, 0xff, 0xda, 0x00, 0xff, 0xff, 0xdb, 0x00,
  0xff, 0xff, 0xdc, 0x00, 0xff, 0xff, 0xdd, 0x00, 0xff, 0xff, 0xde, 0x00,
  0xff, 0xff, 0xdf, 0x00, 0xff, 0xff, 0x92, 0x25, 0xff, 0xff, 0xa1, 0x00,
  0xff, 0xff, 0xa2, 0x00, 0xff, 0xff, 0xa3, 0x00, 0xff, 0xff, 0xac, 0x20,
  0xff, 0xff, 0xa5, 0x00, 0xff, 0xff, 0x60, 0x01, 0xff, 0xff, 0xa7, 0x00,
  0xff, 0xff, 0x61, 0x01, 0xff, 0xff, 0xa9, 0x00, 0xff, 0xff, 0xaa, 0x00,
  0xff, 0xff, 0xab, 0x00, 0xff, 0xff, 0xac, 0x00, 0xff, 0xff, 0xa4, 0x00,
  0xff, 0xff, 0xae, 0x00, 0xff, 0xff, 0xaf, 0x00, 0xc9, 0x02, 0xff, 0xff,
  0xb0, 0x00, 0xda, 0x02, 0xff, 0xff, 0xb1, 0x00, 0xff, 0xff, 0xb2, 0x00,
  0xff, 0xff, 0xb3, 0x00, 0xff, 0xff, 0x7d, 0x01, 0xff, 0xff, 0xb5, 0x00,
  0xbc, 0x03, 0xff, 0xff, 0xb6, 0x00, 0xff, 0xff, 0xb7, 0x00, 0x27, 0x20,
  0xc5, 0x22, 0x31, 0x2e, 0xff, 0xff, 0x7e, 0x01, 0xff, 0xff, 0xb9, 0x00,
  0xff, 0xff, 0xba, 0x00, 0xff, 0xff, 0xbb, 0x00, 0xff, 0xff, 0x52, 0x01,
  0xff, 0xff, 0x53, 0x01, 0xff, 0xff, 0x78, 0x01, 0xff, 0xff, 0xbf, 0x00,
  0xff, 0xff, 0x00, 0x25, 0x14, 0x20, 0x15, 0x20, 0xaf, 0x23, 0xff, 0xff,
  0x02, 0x25, 0xff, 0xff, 0x0c, 0x25, 0x6d, 0x25, 0xff, 0xff, 0x10, 0x25,
  0x6e, 0x25, 0xff, 0xff, 0x14, 0x25, 0x70, 0x25, 0xff, 0xff, 0x18, 0x25,
  0x6f, 0x25, 0xff, 0xff, 0x1c, 0x25, 0xff, 0xff, 0x24, 0x25, 0xff, 0xff,
  0x2c, 0x25, 0xff, 0xff, 0x34, 0x25, 0xff, 0xff, 0x3c, 0x25, 0xff, 0xff,
  0x91, 0x25, 0xff, 0xff, 0xba, 0x23, 0x3e, 0x20, 0xff, 0xff, 0xbb, 0x23,
  0xff, 0xff, 0xbc, 0x23, 0xff, 0xff, 0xbd, 0x23, 0xff, 0xff, 0x50, 0x25,
  0x01, 0x25, 0xff, 0xff, 0x51, 0x25, 0x03, 0x25, 0xff, 0xff, 0x54, 0x25,
  0x0f, 0x25, 0xff, 0xff, 0x57, 0x25, 0x13, 0x25, 0xff, 0xff, 0x5a, 0x25,
  0x17, 0x25, 0xff, 0xff, 0x5d, 0x25, 0x1b, 0x25, 0xff, 0xff, 0x60, 0x25,
  0x23, 0x25, 0xff, 0xff, 0x63, 0x25, 0x2b, 0x25, 0xff, 0xff, 0x66, 0x25,
  0x33, 0x25, 0xff, 0xff, 0x69, 0x25, 0x3b, 0x25, 0xff, 0xff, 0x6c, 0x25,
  0x4b, 0x25, 0xff, 0xff, 0x88, 0x25, 0xff, 0xff, 0x91, 0x21, 0xff, 0xff,
  0x93, 0x21, 0xff, 0xff, 0x90, 0x21, 0xff, 0xff, 0x92, 0x21, 0xff, 0xff,
  0xe0, 0x00, 0xff, 0xff, 0xe1, 0x00, 0xff, 0xff, 0xe2, 0x00, 0xff, 0xff,
  0xe3, 0x00, 0xff, 0xff, 0xe4, 0x00, 0xff, 0xff, 0xe5, 0x00, 0xff, 0xff,
  0xe6, 0x00, 0xff, 0xff, 0xe7, 0x00, 0xff, 0xff, 0xe8, 0x00, 0xff, 0xff,
  0xe9, 0x00, 0xff, 0xff, 0xea, 0x00, 0xff, 0xff, 0xeb, 0x00, 0xff, 0xff,
  0xec, 0x00, 0xff, 0xff, 0xed, 0x00, 0xff, 0xff, 0xee, 0x00, 0xff, 0xff,
  0xef, 0x00, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xf1, 0x00, 0xff, 0xff,
  0xf2, 0x00, 0xff, 0xff, 0xf3, 0x00, 0xff, 0xff, 0xf4, 0x00, 0xff, 0xff,
  0xf5, 0x00, 0xff, 0xff, 0xf6, 0x00, 0xff, 0xff, 0xf7, 0x00, 0xff, 0xff,
  0xf8, 0x00, 0xff, 0xff, 0xf9, 0x00, 0xff, 0xff, 0xfa, 0x00, 0xff, 0xff,
  0xfb, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xfd, 0x00, 0xff, 0xff,
  0xfe, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff
};

void scrollup()
{
    for (int y = 0; y < 720 - 8; y++)
    {
        for (int x = 0; x < 1280; x++)
        {
            int color = get_pixel(x, y + 8);
            set_pixel(x, y, color);
        }
    }
    draw_rect(0, 720 - 8, 1280, 8, 0x000000);
    swap_framebuffers();
}

void draw_char(char c, int x, int y, uint32_t col)
{
    uint8_t *offset = default_font + sizeof(font_header_t) + 16 * c;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (offset[i] & (1 << j))
            {
                setpixel(x + 8 - j, y + i, col);
            }
        }
    }
}
void draw_string(char *string, int x, int y, uint32_t col)
{
    cursorx = x;
    cursory = y;
    
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == '\n')
        {
            cursorx = 0;
            cursory += CHAR_HEIGHT;
            if (cursory >= 720)
            {
                scrollup();
                cursory -= CHAR_HEIGHT;
            }
        }
        else
        {
            draw_char(string[i], cursorx, cursory, col);
            cursorx += CHAR_WIDTH;
            if (cursorx >= 1280)
            {
                cursorx = 0;
                cursory += CHAR_HEIGHT;
                if (cursory >= 720)
                {
                    scrollup();
                    cursory -= CHAR_HEIGHT;
                }
            }
        }
    }
}
