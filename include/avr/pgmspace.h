#pragma once
#include <inttypes.h>

#define prog_uchar uint8_t
#define PROGMEM

inline uint8_t pgm_read_byte(const uint8_t *b) { return *b; }
inline uint16_t pgm_read_word(const uint16_t *w) { return *w; }
