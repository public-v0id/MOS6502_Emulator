#include "bit_manip.h"
#include "mos6502.h"
#include "operations.h"
#include <iostream>

void branch(mos6502* cpu, bool value) {
	cpu->PC += 2;
	if (value) {
		cpu->PC += (int8_t)cpu->get_mem()->get_byte(cpu->PC+1);
	}
}

void compare(uint8_t val, mos6502* cpu, uint8_t ind) {
	uint8_t memval = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(val-memval);
	cpu->set_z(val-memval);
	cpu->set_c(val, (~memval)+1);
	cpu->PC += size[ind];
}
	

uint16_t imm(mos6502* cpu) {
	return cpu->PC+1;
}

uint16_t zp(mos6502* cpu) {
	return cpu->get_mem()->get_byte(cpu->PC+1);
}

uint16_t abs(mos6502* cpu) {
	return (uint16_t(cpu->get_mem()->get_byte(cpu->PC+2))<<8)+cpu->get_mem()->get_byte(cpu->PC+1);
}	

uint16_t zpx(mos6502* cpu) {
	return cpu->get_mem()->get_byte(cpu->PC+1)+cpu->X;
}

uint16_t zpy(mos6502* cpu) {
	return cpu->get_mem()->get_byte(cpu->PC+1)+cpu->Y;
}

uint16_t absx(mos6502* cpu) {
	return (uint16_t(cpu->get_mem()->get_byte(cpu->PC+2))<<8)+cpu->get_mem()->get_byte(cpu->PC+1)+cpu->X;
}

uint16_t absy(mos6502* cpu) {
	return (uint16_t(cpu->get_mem()->get_byte(cpu->PC+2))<<8)+cpu->get_mem()->get_byte(cpu->PC+1)+cpu->Y;
}

uint16_t ind(mos6502* cpu) {//Indirect addressing
	uint16_t LLaddr =  cpu->get_mem()->get_byte(cpu->PC+1)+(((uint16_t)cpu->get_mem()->get_byte(cpu->PC+2))<<8);
	return cpu->get_mem()->get_byte(LLaddr)+(((uint16_t)cpu->get_mem()->get_byte(LLaddr+1))<<8);
}

uint16_t zpxind(mos6502* cpu) {//(ZP, X), indirect
	uint16_t LLaddr = cpu->get_mem()->get_byte(cpu->PC+1)+cpu->X;	
	return cpu->get_mem()->get_byte(LLaddr)+(((uint16_t)cpu->get_mem()->get_byte(LLaddr+1))<<8);
}

uint16_t zpyind(mos6502* cpu) {//(ZP), Y, indirect
	uint16_t LLaddr = cpu->get_mem()->get_byte(cpu->PC+1);
	return cpu->get_mem()->get_byte(LLaddr)+(((uint16_t)cpu->get_mem()->get_byte(LLaddr+1))<<8) + cpu->Y;
}

void LDA(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void LDX(mos6502* cpu, uint8_t ind) {
	cpu->X = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->X);
	cpu->set_z(cpu->X);
	cpu->PC += size[ind];
}

void LDY(mos6502* cpu, uint8_t ind) {
	cpu->Y = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->Y);
	cpu->set_z(cpu->Y);
	cpu->PC += size[ind];
}

void LSR_A(mos6502* cpu, uint8_t ind) {
	cpu->set_c_dir(cpu->AC&1);
	cpu->AC >>= 1;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void JMP(mos6502* cpu, uint8_t ind) {
	std::cout << "ADDR: " << addressing_functions[ind](cpu) << "\n";
	cpu->PC = addressing_functions[ind](cpu);
}

void LSR(mos6502* cpu, uint8_t ind) {
	uint8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_c_dir(val&1);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	val >>= 1;
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), val);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	cpu->set_n(val);
	cpu->set_z(val);
	cpu->PC += size[ind];
}

void ORA(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->AC | cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void EOR(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->AC ^ cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void STA(mos6502* cpu, uint8_t ind) {
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), cpu->AC);
	cpu->PC += size[ind];
}

void STX(mos6502* cpu, uint8_t ind) {
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), cpu->X);
	cpu->PC += size[ind];
}

void STY(mos6502* cpu, uint8_t ind) {
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), cpu->Y);
	cpu->PC += size[ind];
}

void TAX(mos6502* cpu, uint8_t ind) {
	cpu->X = cpu->AC;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void TAY(mos6502* cpu, uint8_t ind) {
	cpu->Y = cpu->AC;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void TSX(mos6502* cpu, uint8_t ind) {
	cpu->X = cpu->SP;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void TXA(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->X;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void TXS(mos6502* cpu, uint8_t ind) {
	cpu->SP = cpu->X;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void TYA(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->Y;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void AND(mos6502* cpu, uint8_t ind) {
	cpu->AC &= cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void BCC(mos6502* cpu, uint8_t ind) {
	branch(cpu, !cpu->get_c());
}

void BCS(mos6502* cpu, uint8_t ind) {
	branch(cpu, cpu->get_c());
}

void BEQ(mos6502* cpu, uint8_t ind) {
	branch(cpu, cpu->get_z());
}

void BNE(mos6502* cpu, uint8_t ind) {
	branch(cpu, !cpu->get_z());
}

void BMI(mos6502* cpu, uint8_t ind) {
	branch(cpu, cpu->get_n());
}

void BPL(mos6502* cpu, uint8_t ind) {
	branch(cpu, !cpu->get_n());
}

void BVC(mos6502* cpu, uint8_t ind) {
	branch(cpu, !cpu->get_v());
}

void BVS(mos6502* cpu, uint8_t ind) {
	branch(cpu, cpu->get_v());
}

void DEC(mos6502* cpu, uint8_t ind) {
	int8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), --val);
	cpu->set_n(val);
	cpu->set_z(val);
	cpu->PC += size[ind];
}

void DEX(mos6502* cpu, uint8_t ind) {
	cpu->X--;
	cpu->set_n(cpu->X);
	cpu->set_z(cpu->X);
	cpu->PC += size[ind];
}

void DEY(mos6502* cpu, uint8_t ind) {
	cpu->Y--;
	cpu->set_n(cpu->Y);
	cpu->set_z(cpu->Y);
	cpu->PC += size[ind];
}

void INC(mos6502* cpu, uint8_t ind) {
	int8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), ++val);
	cpu->set_n(val);
	cpu->set_z(val);
	cpu->PC += size[ind];
}

void INX(mos6502* cpu, uint8_t ind) {
	cpu->X++;
	cpu->set_n(cpu->X);
	cpu->set_z(cpu->X);
	cpu->PC += size[ind];
}

void INY(mos6502* cpu, uint8_t ind) {
	cpu->Y++;
	cpu->set_n(cpu->Y);
	cpu->set_z(cpu->Y);
	cpu->PC += size[ind];
}

void ASL_A(mos6502* cpu, uint8_t ind) {
	cpu->set_c_dir(cpu->AC&128);
	cpu->AC <<= 1;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void ASL(mos6502* cpu, uint8_t ind) {
	uint8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_c_dir(val&128);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	val <<= 1;
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), val);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	cpu->set_n(val);
	cpu->set_z(val);
	cpu->PC += size[ind];
}

void BIT(mos6502* cpu, uint8_t ind) {
	uint8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_z(cpu->AC & val);
	cpu->set_n_dir(get_bit(val, 7));
	cpu->set_v_dir(get_bit(val, 6));
	cpu->PC += size[ind];
}

void CMP(mos6502* cpu, uint8_t ind) {
	compare(cpu->AC, cpu, ind);
}

void CPX(mos6502* cpu, uint8_t ind) {
	compare(cpu->X, cpu, ind);
}

void CPY(mos6502* cpu, uint8_t ind) {
	compare(cpu->Y, cpu, ind);
}

void PHA(mos6502* cpu, uint8_t ind) {
	cpu->push(cpu->AC);
	cpu->PC += size[ind];
}

void PHP(mos6502* cpu, uint8_t ind) {
	cpu->push(cpu->PF);
	cpu->PC += size[ind];
}

void PLA(mos6502* cpu, uint8_t ind) {
	cpu->AC = cpu->pull();
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void PLP(mos6502* cpu, uint8_t ind) {
	cpu->PF = cpu->pull();
	cpu->PC += size[ind];
}

void JSR(mos6502* cpu, uint8_t ind) {
	cpu->push((cpu->PC+2)>>8);
	cpu->push((cpu->PC+2)&0xFF);
	cpu->PC = (uint16_t(cpu->get_mem()->get_byte(cpu->PC+2))<<8)+cpu->get_mem()->get_byte(cpu->PC+1);
	std::cout << "PC is now "<< cpu->PC << "\n";
}

void RTS(mos6502* cpu, uint8_t ind) {
	cpu->PC = cpu->pull();
	cpu->PC += (uint16_t(cpu->pull()))<<8;
	cpu->PC += size[ind];
}

void ROL_A(mos6502* cpu, uint8_t ind) {
	uint8_t c = cpu->get_c() ? 1 : 0;
	cpu->set_c_dir(cpu->AC&128);
	cpu->AC <<= 1;
	cpu->AC += c;
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void ROL(mos6502* cpu, uint8_t ind) {
	uint8_t c = cpu->get_c() ? 1 : 0;
	uint8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_c_dir(val&128);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	val <<= 1;
	val += c;
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), val);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	cpu->set_n(val);
	cpu->set_z(val);
	cpu->PC += size[ind];
}

void ROR_A(mos6502* cpu, uint8_t ind) {
	uint8_t c = cpu->get_c() ? 1 : 0;
	cpu->set_c_dir(cpu->AC&1);
	cpu->AC >>= 1;
	cpu->AC += (c<<7);
	cpu->set_n(cpu->AC);
	cpu->set_z(cpu->AC);
	cpu->PC += size[ind];
}

void ROR(mos6502* cpu, uint8_t ind) {
	uint8_t c = cpu->get_c() ? 1 : 0;
	uint8_t val = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	cpu->set_c_dir(val&1);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	val >>= 1;
	val += (c<<7);
	cpu->get_mem()->set_byte(addressing_functions[ind](cpu), val);
	std::cout << "Val is " << (((unsigned)val)&0xFF) << "\n";
	cpu->set_n(val);
	cpu->set_z(val);
	cpu->PC += size[ind];
}

void NOP(mos6502* cpu, uint8_t ind) {
	cpu->PC += size[ind];
}

void CLC(mos6502* cpu, uint8_t ind) {
	cpu->set_c_dir(false);
	cpu->PC += size[ind];
}

void CLD(mos6502* cpu, uint8_t ind) {
	cpu->set_d_dir(false);
	cpu->PC += size[ind];
}

void CLI(mos6502* cpu, uint8_t ind) {
	cpu->set_i_dir(false);
	cpu->PC += size[ind];
}

void CLV(mos6502* cpu, uint8_t ind) {
	cpu->set_v_dir(false);
	cpu->PC += size[ind];
}

void SEC(mos6502* cpu, uint8_t ind) {
	cpu->set_c_dir(true);
	cpu->PC += size[ind];
}

void SED(mos6502* cpu, uint8_t ind) {
	cpu->set_d_dir(true);
	cpu->PC += size[ind];
}

void SEI(mos6502* cpu, uint8_t ind) {
	cpu->set_i_dir(true);
	cpu->PC += size[ind];
}

void RTI(mos6502* cpu, uint8_t ind) {
	cpu->set_PF(cpu->pull());
	cpu->PC = cpu->pull();
	cpu->PC += (uint16_t(cpu->pull()))<<8;
	cpu->PC += size[ind];
}

void ADC(mos6502* cpu, uint8_t ind) {
	uint8_t op = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	uint8_t res = cpu->AC+op+(cpu->get_c() ? 1 : 0);
	cpu->set_v(cpu->AC, op, (cpu->get_c() ? 1 : 0));
	cpu->set_c(cpu->AC, op, (cpu->get_c() ? 1 : 0));
	cpu->set_z(res);
	cpu->set_n(res);
	cpu->AC = res;
	cpu->PC += size[ind];
}

void SBC(mos6502* cpu, uint8_t ind) {
	uint8_t op = cpu->get_mem()->get_byte(addressing_functions[ind](cpu));
	uint8_t res = cpu->AC-op-(cpu->get_c() ? 0 : 1);
	cpu->set_v(cpu->AC, ~op, (cpu->get_c() ? 1 : 0));
	cpu->set_c(cpu->AC, (~op)+1, (cpu->get_c() ? 0 : 1));
	cpu->set_z(res);
	cpu->set_n(res);
	cpu->AC = res;
	cpu->PC += size[ind];
}

void (*operations[256])(mos6502*, uint8_t) = {nullptr};
uint16_t (*addressing_functions[256])(mos6502*) = {nullptr};
uint8_t size[256] = {1};
static bool init = [](){
	//LDA
	size[161] = 2;
	size[165] = 2;
	size[169] = 2;
	size[173] = 3;
	size[177] = 2;
	size[181] = 2;
	size[185] = 3;
	size[189] = 3;
	//LDX
	size[162] = 2;
	size[166] = 2;
	size[174] = 3;
	size[182] = 2;
	size[190] = 3;
	//LDY
	size[160] = 2;
	size[164] = 2;
	size[172] = 3;
	size[180] = 2;
	size[188] = 3;
	//LSR
	size[70] = 2;
	size[74] = 1;
	size[78] = 3;
	size[86] = 2;
	size[94] = 3;
	//JMP
	size[76] = 3;
	size[108] = 3;
	//ORA
	size[1] = 2;
	size[5] = 2;
	size[9] = 2;
	size[13] = 3;
	size[17] = 2;
	size[21] = 2;
	size[25] = 3;
	size[29] = 3;
	//STA
	size[0x81] = 2;
	size[0x85] = 2;
	size[0x8D] = 3;
	size[0x91] = 2;
	size[0x95] = 2;
	size[0x99] = 3;
	size[0x9D] = 3;
	//STX
	size[0x86] = 2;
	size[0x8E] = 3;
	size[0x96] = 2;
	//STY
	size[0x84] = 2;
	size[0x8C] = 3;
	size[0x94] = 2;
	//T...
	size[0x8A] = 1;
	size[0x9A] = 1;
	size[0x98] = 1;
	size[0xAA] = 1;
	size[0xA8] = 1;
	size[0xBA] = 1;
	//AND
	size[0x21] = 2;
	size[0x25] = 2;
	size[0x29] = 2;
	size[0x2D] = 3;
	size[0x31] = 2;
	size[0x35] = 2;
	size[0x39] = 3;
	size[0x3D] = 3;
	//DE..
	size[0x88] = 1;
	size[0xC6] = 2;
	size[0xCA] = 1;
	size[0xCE] = 3;
	size[0xD6] = 2;
	size[0xDE] = 3;
	//IN..
	size[0xE6] = 2;
	size[0xE8] = 1;	
	size[0xC8] = 1;
	size[0xEE] = 3;
	size[0xF6] = 2;
	size[0xFE] = 3;
	//EOR
	size[0x41] = 2;
	size[0x45] = 2;
	size[0x49] = 2;
	size[0x4D] = 3;
	size[0x51] = 2;
	size[0x55] = 2;
	size[0x59] = 3;
	size[0x5D] = 3;
	//ASL
	size[0x06] = 2;
	size[0x0A] = 1;
	size[0x0E] = 3;
	size[0x16] = 2;
	size[0x1E] = 3;
	//BIT
	size[0x24] = 2;
	size[0x2C] = 3;
	//CMP
	size[0xC1] = 2;
	size[0xC5] = 2;
	size[0xC9] = 2;
	size[0xCD] = 3;
	size[0xD1] = 2;
	size[0xD5] = 2;
	size[0xD9] = 3;
	size[0xDD] = 3;
	//CPX
	size[0xE0] = 2;
	size[0xE4] = 2;
	size[0xEC] = 3;
	//CPY
	size[0xC0] = 2;
	size[0xC4] = 2;
	size[0xCC] = 3;
	//Stack operations
	size[0x08] = 1;
	size[0x28] = 1;
	size[0x48] = 1;
	size[0x68] = 1;
	//Subroutines
	size[0x20] = 3;
	size[0x60] = 1;
	//ROL
	size[0x26] = 2;
	size[0x2A] = 1;
	size[0x2E] = 3;
	size[0x36] = 2;
	size[0x3E] = 3;
	//ROR
	size[0x66] = 2;
	size[0x6A] = 1;
	size[0x6E] = 3;
	size[0x76] = 2;
	size[0x7E] = 3;
	//NOP
	size[0xEA] = 1;
	//set/clear operations
	size[0x18] = 1;
	size[0x38] = 1;
	size[0x58] = 1;
	size[0x78] = 1;
	size[0xB8] = 1;
	size[0xD8] = 1;
	size[0xF8] = 1;
	//ADC
	size[0x61] = 2;
	size[0x65] = 2;
	size[0x69] = 2;
	size[0x6D] = 3;
	size[0x71] = 2;
	size[0x75] = 2;
	size[0x79] = 3;
	size[0x7D] = 3;
	//SBC
	size[0xE1] = 2;
	size[0xE5] = 2;
	size[0xE9] = 2;
	size[0xED] = 3;
	size[0xF1] = 2;
	size[0xF5] = 2;
	size[0xF9] = 3;
	size[0xFD] = 3;
	//LDA
	addressing_functions[161] = zpxind;
	addressing_functions[165] = zp;
	addressing_functions[169] = imm;
	addressing_functions[173] = abs;
	addressing_functions[177] = zpyind;
	addressing_functions[181] = zpx;
	addressing_functions[185] = absy;
	addressing_functions[189] = absx;
	//LDX
	addressing_functions[162] = imm;
	addressing_functions[166] = zp;
	addressing_functions[174] = abs;
	addressing_functions[182] = zpy;
	addressing_functions[190] = absy;
	//LDY
	addressing_functions[160] = imm;
	addressing_functions[164] = zp;
	addressing_functions[172] = abs;
	addressing_functions[180] = zpx;
	addressing_functions[188] = absx;
	//LSR
	addressing_functions[70] = zp;
	addressing_functions[78] = abs;
	addressing_functions[86] = zpx;
	addressing_functions[94] = absx;
	//JMP
	addressing_functions[76] = abs;
	addressing_functions[108] = ind;
	//ORA
	addressing_functions[1] = zpxind;
	addressing_functions[5] = zp;
	addressing_functions[9] = imm;
	addressing_functions[13] = abs;
	addressing_functions[17] = zpyind;
	addressing_functions[21] = zpx;
	addressing_functions[25] = absy;
	addressing_functions[29] = absx;
	//STA
	addressing_functions[0x81] = zpxind;
	addressing_functions[0x85] = zp;
	addressing_functions[0x8D] = abs;
	addressing_functions[0x91] = zpyind;
	addressing_functions[0x95] = zpx;
	addressing_functions[0x99] = absy;
	addressing_functions[0x9D] = absx;
	//STX
	addressing_functions[0x86] = zp;
	addressing_functions[0x8E] = abs;
	addressing_functions[0x96] = zpy;
	//STY
	addressing_functions[0x84] = zp;
	addressing_functions[0x8C] = abs;
	addressing_functions[0x94] = zpx;
	//AND
	addressing_functions[0x21] = zpxind;
	addressing_functions[0x25] = zp;
	addressing_functions[0x29] = imm;
	addressing_functions[0x2D] = abs;
	addressing_functions[0x31] = zpyind;
	addressing_functions[0x35] = zpx;
	addressing_functions[0x39] = absy;
	addressing_functions[0x3D] = absx;
	//DEC
	addressing_functions[0xC6] = zp;
	addressing_functions[0xCE] = abs;
	addressing_functions[0xD6] = zpx;
	addressing_functions[0xDE] = absx;
	//INC
	addressing_functions[0xE6] = zp;
	addressing_functions[0xEE] = abs;
	addressing_functions[0xF6] = zpx;
	addressing_functions[0xFE] = absx;
	//EOR
	addressing_functions[0x41] = zpxind;
	addressing_functions[0x45] = zp;
	addressing_functions[0x49] = imm;
	addressing_functions[0x4D] = abs;
	addressing_functions[0x51] = zpyind;
	addressing_functions[0x55] = zpx;
	addressing_functions[0x59] = absy;
	addressing_functions[0x5D] = absx;
	//ASL
	addressing_functions[0x06] = zp;
	addressing_functions[0x0E] = abs;
	addressing_functions[0x16] = zpx;
	addressing_functions[0x1E] = absx;
	//BIT
	addressing_functions[0x24] = zp;
	addressing_functions[0x2C] = abs;
	//CMP
	addressing_functions[0xC1] = zpxind;
	addressing_functions[0xC5] = zp;
	addressing_functions[0xC9] = imm;
	addressing_functions[0xCD] = abs;
	addressing_functions[0xD1] = zpyind;
	addressing_functions[0xD5] = zpx;
	addressing_functions[0xD9] = absy;
	addressing_functions[0xDD] = absx;
	//CPX
	addressing_functions[0xE0] = imm;
	addressing_functions[0xE4] = zp;
	addressing_functions[0xEC] = abs;
	//CPY
	addressing_functions[0xC0] = imm;
	addressing_functions[0xC4] = zp;
	addressing_functions[0xCC] = abs;
	//ROL
	addressing_functions[0x26] = zp;
	addressing_functions[0x2E] = abs;
	addressing_functions[0x36] = zpx;
	addressing_functions[0x3E] = absx;
	//ROR
	addressing_functions[0x66] = zp;
	addressing_functions[0x6E] = abs;
	addressing_functions[0x76] = zpx;
	addressing_functions[0x7E] = absx;
	//ADC
	addressing_functions[0x61] = zpxind;
	addressing_functions[0x65] = zp;
	addressing_functions[0x69] = imm;
	addressing_functions[0x6D] = abs;
	addressing_functions[0x71] = zpyind;
	addressing_functions[0x75] = zpx;
	addressing_functions[0x79] = absy;
	addressing_functions[0x7D] = absx;
	//SBC
	addressing_functions[0xE1] = zpxind;
	addressing_functions[0xE5] = zp;
	addressing_functions[0xE9] = imm;
	addressing_functions[0xED] = abs;
	addressing_functions[0xF1] = zpyind;
	addressing_functions[0xF5] = zpx;
	addressing_functions[0xF9] = absy;
	addressing_functions[0xFD] = absx;
	//LDA
	operations[161] = LDA;
	operations[165] = LDA;
	operations[169] = LDA;
	operations[173] = LDA;
	operations[177] = LDA;
	operations[181] = LDA;
	operations[185] = LDA;
	operations[189] = LDA;
	//LDX
	operations[162] = LDX;
	operations[166] = LDX;
	operations[174] = LDX;
	operations[182] = LDX;
	operations[190] = LDX;
	//LDY
	operations[160] = LDY;
	operations[164] = LDY;
	operations[172] = LDY;
	operations[180] = LDY;
	operations[188] = LDY;
	//LSR
	operations[70] = LSR;
	operations[74] = LSR_A;
	operations[78] = LSR;
	operations[86] = LSR;
	operations[94] = LSR;
	//JMP
	operations[76] = JMP;
	operations[108] = JMP;
	//ORA
	operations[1] = ORA;
	operations[5] = ORA;
	operations[9] = ORA;
	operations[13] = ORA;
	operations[17] = ORA;
	operations[21] = ORA;
	operations[25] = ORA;
	operations[29] = ORA;
	//STA
	operations[0x81] = STA;
	operations[0x85] = STA;
	operations[0x8D] = STA;
	operations[0x91] = STA;
	operations[0x95] = STA;
	operations[0x99] = STA;
	operations[0x9D] = STA;
	//STX
	operations[0x86] = STX;
	operations[0x8E] = STX;
	operations[0x96] = STX;
	//STY
	operations[0x84] = STY;
	operations[0x8C] = STY;
	operations[0x94] = STY;
	//T...
	operations[0x8A] = TXA;
	operations[0x98] = TYA;
	operations[0x9A] = TXS;
	operations[0xA8] = TAY;
	operations[0xAA] = TAX;
	operations[0xBA] = TSX;
	//AND
	operations[0x21] = AND;
	operations[0x25] = AND;
	operations[0x29] = AND;
	operations[0x2D] = AND;
	operations[0x31] = AND;
	operations[0x35] = AND;
	operations[0x39] = AND;
	operations[0x3D] = AND;
	//B...
	operations[0x10] = BPL;
	operations[0x30] = BMI;
	operations[0x50] = BVC;
	operations[0x70] = BVS;
	operations[0x90] = BCC;
	operations[0xB0] = BCS;
	operations[0xD0] = BNE;
	operations[0xF0] = BEQ;
	//DE...
	operations[0x88] = DEY;
	operations[0xC6] = DEC;
	operations[0xCA] = DEX;
	operations[0xCE] = DEC;
	operations[0xD6] = DEC;
	operations[0xDE] = DEC;
	//IN...
	operations[0xC8] = INY;
	operations[0xE6] = INC;
	operations[0xE8] = INX;
	operations[0xEE] = INC;
	operations[0xF6] = INC;
	operations[0xFE] = INC;
	//EOR
	operations[0x41] = EOR;
	operations[0x45] = EOR;
	operations[0x49] = EOR;
	operations[0x4D] = EOR;
	operations[0x51] = EOR;
	operations[0x55] = EOR;
	operations[0x59] = EOR;
	operations[0x5D] = EOR;
	//ASL
	operations[0x06] = ASL;
	operations[0x0A] = ASL_A;
	operations[0x0E] = ASL;
	operations[0x16] = ASL;
	operations[0x1E] = ASL;
	//BIT
	operations[0x24] = BIT;
	operations[0x2C] = BIT;
	//CMP
	operations[0xC1] = CMP;
	operations[0xC5] = CMP;
	operations[0xC9] = CMP;
	operations[0xCD] = CMP;
	operations[0xD1] = CMP;
	operations[0xD5] = CMP;
	operations[0xD9] = CMP;
	operations[0xDD] = CMP;
	//CPX
	operations[0xE0] = CPX;
	operations[0xE4] = CPX;
	operations[0xEC] = CPX;
	//CPY
	operations[0xC0] = CPY;
	operations[0xC4] = CPY;
	operations[0xCC] = CPY;
	//Stack operations (PHA, PHP, PLA, PLP)
	operations[0x08] = PHP;
	operations[0x28] = PLP;
	operations[0x48] = PHA;
	operations[0x68] = PLA;
	//Subroutines (JSR, RTS)
	operations[0x20] = JSR;
	operations[0x60] = RTS;
	//ROL
	operations[0x26] = ROL;
	operations[0x2A] = ROL_A;
	operations[0x2E] = ROL;
	operations[0x36] = ROL;
	operations[0x3E] = ROL;
	//ROR
	operations[0x66] = ROR;
	operations[0x6A] = ROR_A;
	operations[0x6E] = ROR;
	operations[0x76] = ROR;
	operations[0x7E] = ROR;
	//NOP
	operations[0xEA] = NOP;
	//set/clear operations
operations[0x18] = CLC;
	operations[0x38] = SEC;
	operations[0x58] = CLI;
	operations[0x78] = SEI;
	operations[0xB8] = CLV;
	operations[0xD8] = CLD;
	operations[0xF8] = SED;
	//ADC
	operations[0x61] = ADC;
	operations[0x65] = ADC;
	operations[0x69] = ADC;
	operations[0x6D] = ADC;
	operations[0x71] = ADC;
	operations[0x75] = ADC;
	operations[0x79] = ADC;
	operations[0x7D] = ADC;
	//SBC
	operations[0xE1] = SBC;
	operations[0xE5] = SBC;
	operations[0xE9] = SBC;
	operations[0xED] = SBC;
	operations[0xF1] = SBC;
	operations[0xF5] = SBC;
	operations[0xF9] = SBC;
	operations[0xFD] = SBC;
	return true;
}();
