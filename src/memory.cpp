#include "../include/memory.h"
#include <iostream>

memory::memory() {
	std::cout << "empty memory initializer\n";
	mem = nullptr;
}

memory::memory(uint16_t size) {
	mem = (uint8_t*)malloc(size*sizeof(uint8_t));
	if (mem == nullptr) {
		std::cout << "error initializing memory!\n";
		return;
	}
	std::cout << "initialized " << size << " bytes of memory at " << static_cast<void*>(mem) << "\n";
}

memory::~memory() {
	if (mem != nullptr) {
		std::cout << "deinitializing memory!\n";
		free(mem);
	}
}
