
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
    if(!cpu._r.c)
        cpu._r.b = (byte) ((cpu._r.b + 1) & 0xFF);
    else
        cpu._r.c = (byte) ((cpu._r.c + 1) & 0xFF);
    cpu._r.m = 1;
}

void opcode_0x04(Z80& cpu)
{
    cpu.add(cpu._r.b, 1);
    cpu._r.m = 1;
}

void opcode_0x05(Z80& cpu)
{
    cpu.sub(cpu._r.b, 1);
    cpu._r.m = 1;
}

void opcode_0x06(Z80& cpu)
{
    cpu._r.b = read_byte(cpu._r.pc++);
    cpu._r.m = 1;
}

void opcode_0x07(Z80& cpu)
{
    byte carry = (byte) (cpu._r.a & 0x80);
    cpu.set_carry(carry);
    cpu.set_operation(0);
    cpu.set_half_carry(0);
    cpu._r.a = (cpu._r.a << 1) + carry;
    if(cpu._r.a == 0)
        cpu.set_zero(1);
    cpu._r.m = 1;
}

void opcode_0x08(Z80& cpu)
{
    write_word(cpu._r.sp, cpu._r.pc);
    cpu._r.pc += 2;
    cpu._r.m = 3;
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
    cpu._r.m = 3;
}

void opcode_0x13(Z80& cpu)
{
    cpu.add(cpu._r.e, 1);
    if(!cpu._r.e)
        cpu.add(cpu._r.d, 1);
    cpu._r.m = 1;
}

void opcode_0x14(Z80& cpu)
{
    cpu.add(cpu._r.d, 1);
    cpu._r.m = 1;
}

void opcode_0x15(Z80& cpu)
{
    cpu.sub(cpu._r.d, 1);
    cpu._r.m = 1;
}

void opcode_0x16(Z80& cpu)
{
    cpu._r.d = read_byte(cpu._r.pc++);
    cpu._r.m = 1;
}

#endif //GBEMU_OPCODES_H
