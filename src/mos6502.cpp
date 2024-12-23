#include "bit_manip.h"
#include "mos6502.h"
#include "operations.h"
#include <iostream>
#include <fstream>
#include <string>

uint8_t inc_7th_bit(uint8_t val1, uint8_t val2) {
	return (val1+val2)>>7 != ((val1>>7)+(val2>>7)) & 1;
}

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

mos6502::mos6502(uint16_t size, std::string file) : mem(size) {
	std::cout << "creating CPU with " << size << " bytes of memory\n";
	AC = 0;
	X = 0;
	Y = 0;
	SP = 0;
	PC = 0;
	PF = 0;
	mem.read_file(file);
	mem.mem_dump();
}

void mos6502::set_n(uint8_t reg) {
	set_bit(PF, 7, reg&128);
}

void mos6502::set_v(uint8_t val1, uint8_t val2) {
	set_bit(PF, 6, ((((uint16_t)val1+(uint16_t)val2)&256)>>8)^inc_7th_bit(val1, val2));
}

void mos6502::set_z(uint8_t reg) {
	set_bit(PF, 1, !reg);
}

void mos6502::set_c(uint8_t val1, uint8_t val2) {
	set_bit(PF, 0, ((uint16_t)val1+(uint16_t)val2)&256);
}

void mos6502::reg_dump() {
	std::cout << "AC: " << ((unsigned)AC&0xFF) << "\nX:  "  << ((unsigned)X&0xFF) << "\nY:  " << ((unsigned)Y&0xFF) << "\nSP: " << ((unsigned)SP&0xFF) << "\nPC: " << ((unsigned)PC&0xFF) << "\nPF: " << ((unsigned)PF&0xFF) << "\n";
}

void mos6502::run() {
	X = 5;
	Y = 16;
	operations[mem.getByte(PC)](this, mem.getByte(PC));
	reg_dump();
}

memory* mos6502::getMem() {
	return &mem;
}
