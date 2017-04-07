
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
    write_byte(cpu._r.a, (word) ((word) (cpu._r.b << 8) + cpu._r.c));
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
    write_word(cpu._r.sp, read_word(cpu._r.pc));
    cpu._r.pc += 2;
    cpu._r.m = 3;
}

void opcode_0x09(Z80& cpu)
{
    cpu.add(cpu._r.h, cpu._r.l, ((word) cpu._r.b << 8) + cpu._r.c);
}

void opcode_0x0A(Z80& cpu)
{
    cpu._r.a = read_byte((word) ((word) cpu._r.b << 8) + cpu._r.c);
    cpu._r.m = 2;
}

void opcode_0x0B(Z80& cpu)
{
    if(!cpu._r.c)
        cpu._r.b = (byte) ((cpu._r.b - 1) & 0xFF);
    else
        cpu._r.c = (byte) ((cpu._r.c - 1) & 0xFF);
    cpu._r.m = 1;
}

void opcode_0x0C(Z80& cpu)
{
    cpu._r.c += 1;
    cpu._r.m = 1;
}

void opcode_0x0D(Z80& cpu)
{
    cpu._r.c -= 1;
    cpu._r.m = 1;
}

void opcode_0x0E(Z80& cpu)
{
    cpu._r.c = read_byte(cpu._r.pc++);
    cpu._r.m = 3;
}

void opcode_0x0F(Z80& cpu)
{
    byte carry = (byte) (cpu._r.a & 0x01);
    cpu.set_carry(carry);
    cpu.set_operation(0);
    cpu.set_half_carry(0);
    cpu._r.a = (cpu._r.a >> 1) + carry;
    if(cpu._r.a == 0)
        cpu.set_zero(1);
    cpu._r.m = 1;
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
    write_byte(cpu._r.a, ((word) cpu._r.d << 8) + cpu._r.e);
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

void opcode_0x17(Z80& cpu)
{
    opcode_0x07(cpu);
}

void opcode_0x18(Z80& cpu)
{
    byte b = read_byte(cpu._r.pc);
    if(b > 127)
        b = (byte) -((!b + 1) & 255);
    cpu._r.pc += b + 1;
    cpu._r.m = 3;
}

void opcode_0x19(Z80& cpu)
{
    cpu.add(cpu._r.h, cpu._r.l, ((word) cpu._r.d << 8) + cpu._r.e);
}

void opcode_0x1A(Z80& cpu)
{
    cpu._r.a = read_byte((word) (cpu._r.d << 8) + cpu._r.e);
    cpu._r.m = 2;
}

void opcode_0x1B(Z80& cpu)
{
    if(!cpu._r.e)
        cpu._r.d = (byte) ((cpu._r.b - 1) & 0xFF);
    else
        cpu._r.e = (byte) ((cpu._r.c - 1) & 0xFF);
    cpu._r.m = 1;
}

void opcode_0x1C(Z80& cpu)
{
    cpu._r.e += 1;
    cpu._r.m = 1;
}

void opcode_0x1D(Z80& cpu)
{
    cpu._r.e -= 1;
    cpu._r.m = 1;
}

void opcode_0x1E(Z80& cpu)
{
    cpu._r.e = read_byte(cpu._r.pc++);
    cpu._r.m = 3;
}

void opcode_0x1F(Z80& cpu)
{
    byte carry = (byte) (cpu._r.a & 0x01);
    cpu.set_operation(0);
    cpu.set_half_carry(0);
    cpu._r.a = (cpu._r.a >> 1) + carry;
    if(cpu._r.a == 0)
        cpu.set_zero(1);
    cpu._r.m = 1;
}

void opcode_0x20(Z80& cpu)
{
    if(!cpu.is_zero())
        opcode_0x18(cpu);
}

void opcode_0x21(Z80& cpu)
{
    cpu._r.l = read_byte(cpu._r.pc);
    cpu._r.h = read_byte((word) (cpu._r.pc + 1));
    cpu._r.pc += 2;
    cpu._r.m = 3;
}

void opcode_0x22(Z80& cpu)
{
    write_byte(cpu._r.a, ((word) cpu._r.h << 8) + cpu._r.l);
    cpu._r.m = 3;
}

void opcode_0x23(Z80& cpu)
{
    cpu.add(cpu._r.l, 1);
    if(!cpu._r.l)
        cpu.add(cpu._r.h, 1);
    cpu._r.m = 1;
}

void opcode_0x24(Z80& cpu)
{
    cpu.add(cpu._r.h, 1);
    cpu._r.m = 1;
}

void opcode_0x25(Z80& cpu)
{

}

void opcode_0x26(Z80& cpu)
{

}

void opcode_0x27(Z80& cpu)
{

}

void opcode_0x28(Z80& cpu)
{
    byte n = read_byte(cpu._r.pc);
    if(n > 127)
        n = (byte) -((!n + 1) & 255);
    cpu._r.pc++;
    cpu._r.m = 2;
    if(cpu.is_zero())
    {
        cpu._r.pc += n;
        cpu._r.m++;
    }
}

void opcode_0x29(Z80& cpu)
{

}

void opcode_0x2A(Z80& cpu)
{

}

void opcode_0x2B(Z80& cpu)
{

}

void opcode_0x2C(Z80& cpu)
{

}

void opcode_0x2D(Z80& cpu)
{

}

void opcode_0x2E(Z80& cpu)
{

}

void opcode_0x2F(Z80& cpu)
{

}

void opcode_0x30(Z80& cpu)
{
    if(!cpu.is_carry())
        opcode_0x18(cpu);
    cpu._r.m = 3;
}

void opcode_0x31(Z80& cpu)
{
    cpu._r.sp = read_word(cpu._r.pc);
    cpu._r.pc += 2;
    cpu._r.m = 3;
}

void opcode_0x32(Z80& cpu)
{
    word HL = ((word) cpu._r.h << 8) + cpu._r.l;
    write_byte(cpu._r.a, HL);
    cpu.sub(cpu._r.h, cpu._r.l, 1);
    cpu._r.m = 4; // TODO unable to find m so guessed it is m(12) + m(0B)
}

void opcode_0x33(Z80& cpu)
{
    cpu.add(cpu._r.sp, 1);
    cpu._r.m = 1;
}

void opcode_0x34(Z80& cpu)
{
    word addr = ((word) cpu._r.h << 8) + cpu._r.l;
    byte val = (byte) ((read_byte(addr) + 1) & 255);
    write_byte(val, addr);
    cpu.reset_flags();
    cpu.set_zero(val == 0);
    cpu._r.m = 3;
}

void opcode_0x35(Z80& cpu)
{
    word addr = ((word) cpu._r.h << 8) + cpu._r.l;
    byte val = (byte) ((read_byte(addr) - 1) & 255);
    write_byte(val, addr);
    cpu.reset_flags();
    cpu.set_zero(val == 0);
    cpu._r.m = 3;
}

void opcode_0x36(Z80& cpu)
{
    word addr = ((word) cpu._r.h << 8) + cpu._r.l;
    write_byte(read_byte(cpu._r.pc), addr);
    cpu._r.pc++;
    cpu._r.m = 3;
}

void opcode_0x37(Z80& cpu)
{
    cpu.set_carry(1);
    cpu._r.m = 1;
}

void opcode_0x38(Z80& cpu)
{
    byte n = read_byte(cpu._r.pc);
    if(n > 127)
        n = (byte) -((!n + 1) & 255);
    cpu._r.pc++;
    cpu._r.m = 2;
    if(cpu.is_carry())
    {
        cpu._r.pc += n;
        cpu._r.m++;
    }
}

void opcode_0x39(Z80& cpu)
{
    cpu.add(cpu._r.h, cpu._r.l, cpu._r.sp);
    cpu._r.m = 3;
}


void opcode_0x40(Z80& cpu)
{
    opcode_0x00(); // y u du dis Z80 ?
}

void opcode_0x41(Z80& cpu)
{
    cpu._r.b = cpu._r.c;
    cpu._r.m = 1;
}

void opcode_0x42(Z80& cpu)
{
    cpu._r.b = cpu._r.d;
    cpu._r.m = 1;
}

void opcode_0x43(Z80& cpu)
{
    cpu._r.b = cpu._r.e;
    cpu._r.m = 1;
}

void opcode_0x44(Z80& cpu)
{
    cpu._r.b = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x45(Z80& cpu)
{
    cpu._r.b = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x46(Z80& cpu)
{
    word addr = ((word) cpu._r.h << 8) + cpu._r.l;
    cpu._r.b = read_byte(addr);
    cpu._r.m = 2;
}

void opcode_0x47(Z80& cpu)
{
    cpu._r.b = cpu._r.a;
    cpu._r.m = 1;
}

void opcode_0x48(Z80& cpu)
{
    cpu._r.c = cpu._r.b;
    cpu._r.m = 1;
}

void opcode_0x49(Z80& cpu)
{
    opcode_0x00();
}

void opcode_0x4A(Z80& cpu)
{
    cpu._r.c = cpu._r.d;
    cpu._r.m = 1;
}

void opcode_0x4B(Z80& cpu)
{
    cpu._r.c = cpu._r.e;
    cpu._r.m = 1;
}

void opcode_0x4C(Z80& cpu)
{
    cpu._r.c = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x4D(Z80& cpu)
{
    cpu._r.c = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x4E(Z80& cpu)
{
    word addr = ((word) cpu._r.h << 8) + cpu._r.l;
    cpu._r.c = read_byte(addr);
    cpu._r.m = 2;
}

void opcode_0x4F(Z80& cpu)
{
    cpu._r.c = cpu._r.a;
    cpu._r.m = 1;
}

void opcode_0x50(Z80& cpu)
{

}

void opcode_0x51(Z80& cpu)
{

}

void opcode_0x52(Z80& cpu)
{

}

void opcode_0x53(Z80& cpu)
{

}

void opcode_0x54(Z80& cpu)
{

}

void opcode_0x55(Z80& cpu)
{

}

void opcode_0x56(Z80& cpu)
{

}

void opcode_0x57(Z80& cpu)
{

}

void opcode_0x58(Z80& cpu)
{

}

void opcode_0x59(Z80& cpu)
{

}

void opcode_0x5A(Z80& cpu)
{

}

void opcode_0x5B(Z80& cpu)
{

}

void opcode_0x5C(Z80& cpu)
{

}

void opcode_0x5D(Z80& cpu)
{

}

void opcode_0x5E(Z80& cpu)
{

}

void opcode_0x5F(Z80& cpu)
{

}

void opcode_0x60(Z80& cpu)
{

}

void opcode_0x61(Z80& cpu)
{

}

void opcode_0x62(Z80& cpu)
{

}

void opcode_0x63(Z80& cpu)
{

}

void opcode_0x64(Z80& cpu)
{

}

void opcode_0x65(Z80& cpu)
{

}

void opcode_0x66(Z80& cpu)
{

}

void opcode_0x67(Z80& cpu)
{

}

void opcode_0x68(Z80& cpu)
{

}

void opcode_0x69(Z80& cpu)
{

}

void opcode_0x6A(Z80& cpu)
{

}

void opcode_0x6B(Z80& cpu)
{

}

void opcode_0x6C(Z80& cpu)
{

}

void opcode_0x6D(Z80& cpu)
{

}

void opcode_0x6E(Z80& cpu)
{

}

void opcode_0x6F(Z80& cpu)
{

}


#endif //GBEMU_OPCODES_H
