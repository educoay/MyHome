#ifndef ICONDEL_H
#define ICONDEL_H

#include <avr/pgmspace.h>

#define icon_del_width 10
#define icon_del_height 10

const  unsigned char icon_del_bits[] PROGMEM = {
   0x03, 0x00, 0x05, 0x00, 0x05, 0x00, 0x3b, 0x00, 0x08, 0x00, 0x18, 0x00,
   0x78, 0x00, 0x40, 0x00, 0x40, 0x00, 0xc0, 0x01 };


#endif