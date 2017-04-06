
#ifndef GBEMU_OPCODES_H
#define GBEMU_OPCODES_H

#include "CPU.h"
#include "GUI.h"
#include "MMU.h"

void opcode_0x00()
{
    asm
    {
        NOP
    }
}

void opcode_0x10()
{
    while(!gameboy_keys_pressed()) // TODO is this legit?
    {}
}

void opcode_0x11(Z80& cpu)
{
    
}

#endif //GBEMU_OPCODES_H
