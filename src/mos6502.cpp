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
	set_bit(PF, 1, reg == 0);
}

void mos6502::set_c(uint8_t val1, uint8_t val2) {
	set_bit(PF, 0, ((uint16_t)val1+(uint16_t)val2)&256);
}

void mos6502::set_c(bool val) {
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
	reg_dump();
}

void mos6502::push(uint8_t val) {
	if (SP <= 255) {
		mem.set_byte(SP+256, val);
		SP += (SP < 255) ? 1 : 0;
	}
	else {
		std::cout << "Error! Stack is filled!\n"; //todo: проверить, так ли это работает на машине
	}
}

memory* mos6502::get_mem() {
	return &mem;
}
