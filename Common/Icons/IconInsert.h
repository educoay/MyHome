#ifndef ICONINSERT_H
#define ICONINSERT_H

#include <avr/pgmspace.h>

#define icon_insert_width 10
#define icon_insert_height 10

const unsigned char icon_insert_bits[] PROGMEM = {
   0x07, 0x00, 0x02, 0x00, 0x02, 0x00, 0x2f, 0x00, 0x38, 0x00, 0x28, 0x00,
   0xa8, 0x01, 0xc0, 0x00, 0x80, 0x01, 0xc0, 0x00 };
   
#endif
