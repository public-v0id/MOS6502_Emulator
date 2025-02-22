#include "bit_manip.h"

bool get_bit(uint8_t reg, uint8_t num) {
	return (reg>>num)&1;
}

void set_bit(uint8_t& reg, uint8_t num, bool val) {
	if (val && !((reg>>num)&1)) {
		reg += (1<<num);
	}
	else if (!val && (reg>>num)&1) {
		reg -= (1<<num);
	}
}
