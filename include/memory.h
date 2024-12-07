#pragma once
#include <cstdint>

class memory {
	public:
		memory();
		memory(uint16_t size);
		~memory();
	private:
		uint16_t sz;
		uint8_t* mem;
};
