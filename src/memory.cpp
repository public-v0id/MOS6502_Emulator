#include "memory.h"
#include "hex.h"
#include <iostream>
#include <fstream>

memory::memory(void) {
	std::cout << "empty memory initializer\n";
	mem = nullptr;
}

memory::memory(uint16_t size) {
	mem = (uint8_t*)calloc(size,sizeof(uint8_t));
	if (mem == nullptr) {
		std::cout << "error initializing memory!\n";
		return;
	}
	sz = size;
	std::cout << "initialized " << size << " bytes of memory at " << static_cast<void*>(mem) << "\n";
}

memory::~memory(void) {
	if (mem != nullptr) {
		std::cout << "deinitializing memory!\n";
		free(mem);
	}
}

void memory::read_file(std::string file) {
	std::ifstream inp;
	inp.open(file);
	if (inp.is_open()) {
		std::string addr, val;
		while (inp >> addr) {
			inp >> val;
			uint16_t int_addr = hex_to_uint16(addr);
			if (int_addr >= sz) {
				std::cout << "Unavailable address " << addr <<"!\n";
				continue;
			}
			mem[int_addr] = hex_to_uint8(val);
		}
		inp.close();
	}	
}

void memory::mem_dump(void) {
	std::cout << "dumping " << sz << " bytes of memory at " << static_cast<void*>(mem) << "\n";
	for (uint16_t i = 0; i < sz; ++i) {
		std::cout << i << " : " << unsigned(mem[i]) << "\n";
	}
}

uint8_t memory::get_byte(uint16_t ind) {
	return mem[ind];
}

void memory::set_byte(uint16_t ind, uint8_t val) {
	mem[ind] = val;
	std::cout << "Set " << ind << " as " << (unsigned(val)&0xFF) << "\n";
}
