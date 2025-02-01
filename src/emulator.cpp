#include "mos6502.h"
#include <iostream>

int main() {
	mos6502 mos = mos6502(65536, "memory.txt");
	char cmd = ' ';
	std::cout << "Input command ('R' to run all operations until the end, 'C' to run a single step, 'I' for an IRQ and 'N' for an NMI):\n";
	std::cin >> cmd;
	bool irq = false, nmi = false;
	while (mos.op_available()) {
		switch (cmd) {
			case 'C':
				mos.step();
				mos.dump();
				std::cout << "Input command ('R' to run all operations until the end, 'C' to run a single step, 'I' for an IRQ and 'N' for an NMI):\n";
				std::cin >> cmd;
				break;
			case 'R':
				mos.step();	
				break;
			case 'I':
				mos.irq();
				mos.dump();
				std::cout << "Input command ('R' to run all operations until the end, 'C' to run a single step, 'I' for an IRQ and 'N' for an NMI):\n";
				std::cin >> cmd;
				break;
			case 'N':
				mos.nmi();
				mos.dump();
				std::cout << "Input command ('R' to run all operations until the end, 'C' to run a single step, 'I' for an IRQ and 'N' for an NMI):\n";
				std::cin >> cmd;
				break;
			default:
				std::cout << "Unknown command! Try again!\n";
				std::cin >> cmd;
		}
	}
	return 0;
}
