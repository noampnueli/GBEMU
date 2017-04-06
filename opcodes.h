
#ifndef GBEMU_OPCODES_H
#define GBEMU_OPCODES_H

#include "CPU.h"
#include "MMU.h"

void opcode_0x00()
{
    asm
    {
        NOP
    }
}

#endif //GBEMU_OPCODES_H
