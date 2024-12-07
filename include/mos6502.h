#pragma once
#include "memory.h"
#include <cstdint>

class mos6502 {
	public:
		mos6502();
	       	mos6502(uint16_t memsize);
	private:
		int8_t AC;	//Accumulator
		int8_t X;	//X index
		int8_t Y;	//Y index
		uint8_t SP;	//Stack Pointer
		uint16_t PC;	//Program Counter
		uint8_t PF;	//Processor Flags
		memory mem;
		void setFlag(char flag, bool val);
};
