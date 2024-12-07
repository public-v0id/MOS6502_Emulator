#include "../include/mos6502.h"
#include <iostream>

mos6502::mos6502() {
	std::cout << "creating CPU with " << 4096 << " bytes of memory\n";	
	mos6502(4096);
}

mos6502::mos6502(uint16_t size) : mem(size) {
	std::cout << "creating CPU with " << size << " bytes of memory\n";
	AC = 0;
	X = 0;
	Y = 0;
	SP = 0;
	PC = 0;
	PF = 0;
}
