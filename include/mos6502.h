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
		memory* get_mem();
		void set_n(uint8_t reg);
		void set_n_dir(bool val);
		void set_v(uint8_t val1, uint8_t val2);
		void set_v_dir(bool val);
		void set_z(uint8_t reg);
		void set_c(uint8_t val1, uint8_t val2);
		void set_c_dir(bool val);
		bool get_n();
		bool get_v();
		bool get_z();
		bool get_c();
		void push(uint8_t val);
		uint8_t pull();
		void run();
	private:
		memory mem;	
		void reg_dump();
};
