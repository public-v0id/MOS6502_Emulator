#include "mos6502.h"

int main() {
	mos6502 mos = mos6502(4096, "memory.txt");
	mos.run();
	return 0;
}
