//
// Created by bubz on 4/6/17.
//

#ifndef GBEMU_OPCODES_H
#define GBEMU_OPCODES_H

#include "CPU.h"

void add_registers(Z80& cpu, byte& reg1, byte& reg2)
{
    reg1 += reg2;
    if(reg1 == 0)
        cpu.set_zero(1);
}

#endif //GBEMU_OPCODES_H
