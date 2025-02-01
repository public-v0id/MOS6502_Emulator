#pragma once
#include <cstdint>
#include <string>

class memory {
	public:
		memory(void);
		memory(uint32_t size);
		~memory(void);
		uint8_t get_byte(uint16_t ind);
		void set_byte(uint16_t ind, uint8_t val);
		void read_file(std::string file);
		void mem_dump(void);
	private:
		uint32_t sz;
		uint8_t* mem;
};
