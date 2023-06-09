#include <stdint.h>
static uint32_t roundToNextHighestPowerOf2(uint32_t c) {
  c--;
  c |= c >> 1;
  c |= c >> 2;
  c |= c >> 4;
  c |= c >> 8;
  c |= c >> 16;
  c++;
  c += (c == 0); 
  return c;
}


void set_bits(volatile uint32_t *value, uint32_t bits, uint32_t shift) {
  *value &= ~((roundToNextHighestPowerOf2(bits)-1)<<shift);
  *value |= bits << shift;
}


