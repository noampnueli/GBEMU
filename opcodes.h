
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

void opcode_0x01(Z80& cpu)
{
    cpu._r.c = read_byte(cpu._r.pc);
    cpu._r.b = read_byte((word) (cpu._r.pc + 1));
    cpu._r.pc += 2;
    cpu._r.m = 3;
}

void opcode_0x02(Z80& cpu)
{
    write_byte(cpu._r.a, (word) ((cpu._r.b << 8) + cpu._r.c));
    cpu._r.m = 2;
}
void opcode_0x03(Z80& cpu)
{

}

void opcode_0x10()
{
    while(!gameboy_keys_pressed()) // TODO is this legit?
    {}
}

void opcode_0x11(Z80& cpu)
{
    cpu._r.e = read_byte(cpu._r.pc);
    cpu._r.d = read_byte((word) (cpu._r.pc + 1));
    cpu._r.pc += 2;
    cpu._r.m = 3;
}

void opcode_0x12(Z80& cpu)
{
    write_byte(cpu._r.a, (cpu._r.d << 8) + cpu._r.e);
}

void opcode_0x13(Z80& cpu)
{
    cpu._r.e = (cpu._r.e + 1) & 255;
    cpu.add(&cpu._r.e,1);
}

#endif //GBEMU_OPCODES_H