#include "../include/bit_manip.h"

bool get_bit(uint8_t reg, uint8_t num) {
	return (reg>>num)&1;
}
