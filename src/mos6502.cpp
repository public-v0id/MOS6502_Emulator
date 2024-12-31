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
	SP = 0xFF;
	PC = 0;
	PF = 0;
}

mos6502::mos6502(uint16_t size, std::string file) : mem(size) {
	std::cout << "creating CPU with " << size << " bytes of memory\n";
	AC = 0;
	X = 0;
	Y = 0;
	SP = 0xFF;
	PC = 0;
	PF = 0;
	mem.read_file(file);	
}

void mos6502::set_n(uint8_t reg) {
	set_bit(PF, 7, reg&128);
}

void mos6502::set_n_dir(bool val) {
	set_bit(PF, 7, val);
}

void mos6502::set_v(uint8_t val1, uint8_t val2) {
	set_bit(PF, 6, ((((uint16_t)val1+(uint16_t)val2)&256)>>8)^inc_7th_bit(val1, val2));
}

void mos6502::set_v_dir(bool val) {
	set_bit(PF, 6, val);
}

void mos6502::set_z(uint8_t reg) {
	set_bit(PF, 1, reg == 0);
}

void mos6502::set_c(uint8_t val1, uint8_t val2) {
	set_bit(PF, 0, ((uint16_t)val1+(uint16_t)val2)&256);
}

void mos6502::set_c_dir(bool val) {
	std::cout << "Setting C as " << val << "\n";
	set_bit(PF, 0, val);
}

bool mos6502::get_n() {
	return get_bit(PF, 7);
}

bool mos6502::get_v() {
	return get_bit(PF, 6);
}

bool mos6502::get_z() {
	return get_bit(PF, 1);
}

bool mos6502::get_c() {
	return get_bit(PF, 0);
}

void mos6502::reg_dump() {
	std::cout << "AC: " << ((unsigned)AC&0xFF) << "\nX:  "  << ((unsigned)X&0xFF) << "\nY:  " << ((unsigned)Y&0xFF) << "\nSP: " << ((unsigned)SP&0xFF) << "\nPC: " << ((unsigned)PC&0xFF) << "\nPF: " << ((unsigned)PF&0xFF) << "\n";
}

void mos6502::run() {
	while (operations[mem.get_byte(PC)] != nullptr) {
		std::cout << "PC is " << PC << "\n";
		operations[mem.get_byte(PC)](this, mem.get_byte(PC));
	}
	mem.mem_dump();
	reg_dump();
}

void mos6502::push(uint8_t val) {
	mem.set_byte(SP+256, val);
	std::cout << "Pushing to " << uint16_t(SP)+256 << "\n";
	SP -= 1;
}

uint8_t mos6502::pull() {
	SP += 1;
	std::cout << "Pulling " << uint16_t(SP)+255 << "\n";
	return mem.get_byte(SP+256);
}

memory* mos6502::get_mem() {
	return &mem;
}
