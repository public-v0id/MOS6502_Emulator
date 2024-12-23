#pragma once
#include "mos6502.h"

extern void (*operations[])(mos6502*, uint8_t);
extern uint16_t (*addressing_functions[])(mos6502*);
extern uint8_t size[];
