#include <stdint.h>

static uint32_t roundToNextHighestPowerOf2(uint32_t v) {
 
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  v += (v == 0); 
  return v;
}
void set_bits(volatile uint32_t *value, uint32_t bits, uint32_t shift) {
  *value &= ~((roundToNextHighestPowerOf2(bits)-1)<<shift);
  *value |= bits << shift;
}
