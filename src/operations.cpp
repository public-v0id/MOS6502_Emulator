#include "mos6502.h"
#include "operations.h"
#include <iostream>

uint16_t imm(mos6502* cpu) {
	return cpu->PC+1;
}

uint16_t zp(mos6502* cpu) {
	return cpu->getMem()->getByte(cpu->PC+1);
}

uint16_t abs(mos6502* cpu) {
	return (uint16_t(cpu->getMem()->getByte(cpu->PC+2))<<8)+cpu->getMem()->getByte(cpu->PC+1);
}	

uint16_t zpx(mos6502* cpu) {
	return cpu->getMem()->getByte(cpu->PC+1)+cpu->X;
}

uint16_t absx(mos6502* cpu) {
	return (uint16_t(cpu->getMem()->getByte(cpu->PC+2))<<8)+cpu->getMem()->getByte(cpu->PC+1)+cpu->X;
}

uint16_t absy(mos6502* cpu) {
	return (uint16_t(cpu->getMem()->getByte(cpu->PC+2))<<8)+cpu->getMem()->getByte(cpu->PC+1)+cpu->Y;
}

uint16_t zpxind(mos6502* cpu) {//(ZP, X), indirect
	uint16_t LLaddr = cpu->getMem()->getByte(cpu->PC+1)+cpu->X;	
	return cpu->getMem()->getByte(LLaddr)+(((uint16_t)cpu->getMem()->getByte(LLaddr+1))<<8);
}

uint16_t zpyind(mos6502* cpu) {//(ZP), Y, indirect
	uint16_t LLaddr = cpu->getMem()->getByte(cpu->PC+1);
	return cpu->getMem()->getByte(LLaddr)+(((uint16_t)cpu->getMem()->getByte(LLaddr+1))<<8) + cpu->Y;
}

void LDA(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->getMem()->getByte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void (*operations[256])(mos6502*, uint8_t) = {nullptr};
uint16_t (*addressing_functions[256])(mos6502*) = {nullptr};
uint8_t size[256] = {1};
static bool init = [](){
	size[161] = 2;
	size[165] = 2;
	size[169] = 2;
	size[173] = 3;
	size[177] = 1;
	size[181] = 2;
	size[185] = 3;
	size[189] = 3;
	addressing_functions[161] = zpxind;
	addressing_functions[165] = zp;
	addressing_functions[169] = imm;
	addressing_functions[173] = abs;
	addressing_functions[177] = zpyind;
	addressing_functions[181] = zpx;
	addressing_functions[185] = absy;
	addressing_functions[189] = absx;
	operations[161] = LDA;
	operations[165] = LDA;
	operations[169] = LDA;
	operations[173] = LDA;
	operations[177] = LDA;
	operations[181] = LDA;
	operations[185] = LDA;
	operations[189] = LDA;
	return true;
}();
