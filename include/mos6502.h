#pragma once
#include "memory.h"
#include <cstdint>
#include <string>

class mos6502 {
	public:
		mos6502();
	       	mos6502(uint16_t memsize);
		mos6502(uint16_t memsize, std::string file);
		int8_t AC;	//Accumulator
		int8_t X;	//X index
		int8_t Y;	//Y index
		uint8_t SP;	//Stack Pointer
		uint16_t PC;	//Program Counter
		uint8_t PF;	//Processor Flags
		memory* getMem();
		void set_n(uint8_t reg);
		void set_v(uint8_t val1, uint8_t val2);
		void set_z(uint8_t reg);
		void set_c(uint8_t val1, uint8_t val2);
		void run();
	private:
		memory mem;	
		void reg_dump();
};
