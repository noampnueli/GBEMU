
#ifndef GBEMU_OPCODES_H
#define GBEMU_OPCODES_H


#include "CPU.h"
#include "GUI.h"
#include "MMU.h"
#include "CPU.h"
#include "opmap.h"
#include <csignal>
#include <iostream>

void opcode_0x00(Z80& cpu)
{
    // There was ASM here once
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
    write_byte(cpu._r.a, (((word) cpu._r.b) << 8) + cpu._r.c);
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
    cpu.add(cpu._r.h, cpu._r.l, (((word) cpu._r.b) << 8) + cpu._r.c);
}

void opcode_0x0A(Z80& cpu)
{
    cpu._r.a = read_byte((word) (((word) cpu._r.b) << 8) + cpu._r.c);
    cpu._r.m = 2;
}

void opcode_0x0B(Z80& cpu)
{
    cpu.sub(cpu._r.b, cpu._r.c, 1);
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
    cpu.RR(cpu._r.a, 1);
}

void opcode_0x10(Z80& cpu)
{
    std::cout << "Waiting for key press" << std::endl;
    while(!gameboy_keys_pressed()) // TODO is this legit?
    {}
    std::cout << "Key pressed" << std::endl;
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
    write_byte(cpu._r.a, (((word) cpu._r.d) << 8) + cpu._r.e);
    cpu._r.m = 3;
}

void opcode_0x13(Z80& cpu)
{
    cpu.add(cpu._r.d, cpu._r.e, 1);
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
    sbyte b = read_byte(cpu._r.pc);
    if(b > 127)
        b = (sbyte) ((sbyte) -(~b + 1) & 255);
    cpu._r.pc += b + 1;
    cpu._r.m = 3;
}

void opcode_0x19(Z80& cpu)
{
    cpu.add(cpu._r.h, cpu._r.l, (((word) cpu._r.d) << 8) + cpu._r.e);
}

void opcode_0x1A(Z80& cpu)
{
    cpu._r.a = read_byte((word) (((word) cpu._r.d) << 8) + cpu._r.e);
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
    else
        cpu._r.pc++;
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
    write_byte(cpu._r.a, (((word) cpu._r.h) << 8) + cpu._r.l);
    cpu.add(cpu._r.h, cpu._r.l, 1);
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
    cpu.sub(cpu._r.h, 1);
    cpu._r.m = 1;
}

void opcode_0x26(Z80& cpu)
{
    cpu._r.h = read_byte(cpu._r.pc++);
    cpu._r.m = 1;
}

void opcode_0x27(Z80& cpu)
{
    if(cpu.is_half_carry() || (cpu._r.a & 15) > 9)
        cpu._r.a += 6;
    cpu._r.f &= 0xEF;
    if(cpu.is_half_carry() || cpu._r.a > 0x99)
    {
        cpu._r.a += 0x60;
        cpu.set_carry(1);
    }
    cpu._r.m = 1;
}

void opcode_0x28(Z80& cpu)
{
    sbyte b = read_byte(cpu._r.pc++);
    if(b > 127)
        b = (sbyte) ((sbyte) -(~b + 1) & 255);
    cpu._r.m = 2;
    if(cpu.is_zero())
    {
        cpu._r.pc += b;
        cpu._r.m++;
    }
}

void opcode_0x29(Z80& cpu)
{
    cpu.add(cpu._r.h, cpu._r.l, (((word)cpu._r.h) << 8) + cpu._r.l);
}

void opcode_0x2A(Z80& cpu)
{
    cpu._r.a = read_byte((((word)cpu._r.h) << 8) + cpu._r.l);
    cpu.add(cpu._r.h, cpu._r.l, 1);
}

void opcode_0x2B(Z80& cpu)
{
    if(!cpu._r.l)
        cpu._r.h = (byte) ((cpu._r.b - 1) & 0xFF);
    else
        cpu._r.l = (byte) ((cpu._r.c - 1) & 0xFF);
    cpu._r.m = 1;
}

void opcode_0x2C(Z80& cpu)
{
    cpu.add(cpu._r.l, 1);
    cpu._r.m = 1;
}

void opcode_0x2D(Z80& cpu)
{
    cpu.sub(cpu._r.l, 1);
    cpu._r.m = 1;
}

void opcode_0x2E(Z80& cpu)
{
    cpu._r.l = read_byte(cpu._r.pc++);
    cpu._r.m = 1;
}

void opcode_0x2F(Z80& cpu)
{
    cpu._r.a = ~cpu._r.a;
    cpu.set_operation(1);
    cpu.set_half_carry(1);
}

void opcode_0x30(Z80& cpu)
{
    if(!cpu.is_carry())
        opcode_0x18(cpu);
    else cpu._r.pc++;
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
    word HL = (((word) cpu._r.h) << 8) + cpu._r.l;
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
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    byte val = (byte) ((read_byte(addr) + 1) & 255);
    write_byte(val, addr);
    cpu.reset_flags();
    cpu.set_zero(val == 0);
    cpu._r.m = 3;
}

void opcode_0x35(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    byte val = (byte) ((read_byte(addr) - 1) & 255);
    write_byte(val, addr);
    cpu.reset_flags();
    cpu.set_zero(val == 0);
    cpu._r.m = 3;
}

void opcode_0x36(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
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
    byte n = read_byte(cpu._r.pc++);
    if(n > 127)
        n = (byte) -((!n + 1) & 255);
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

void opcode_0x3A(Z80& cpu)
{
    cpu._r.a = read_byte((((word)cpu._r.h) << 8) + cpu._r.l);
    cpu.sub(cpu._r.h, cpu._r.l, 1);
}

void opcode_0x3B(Z80& cpu)
{
    cpu.sub(cpu._r.sp, 1);
    cpu._r.m = 1;
}

void opcode_0x3C(Z80& cpu)
{
    cpu.add(cpu._r.a, 1);
    cpu._r.m = 1;
}

void opcode_0x3D(Z80& cpu)
{
    cpu.sub(cpu._r.a, 1);
    cpu._r.m = 1;
}

void opcode_0x3E(Z80& cpu)
{
    cpu._r.a = read_byte(cpu._r.pc++);
    cpu._r.m = 1;
}

void opcode_0x3F(Z80& cpu)
{
    cpu.set_carry(0);
}


void opcode_0x40(Z80& cpu)
{
    opcode_0x00(cpu); // y u du dis Z80 ?
    cpu._r.m = 1;
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
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
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
    opcode_0x00(cpu);
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
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
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
    cpu._r.d = cpu._r.b;
    cpu._r.m = 1;
}

void opcode_0x51(Z80& cpu)
{
    cpu._r.d = cpu._r.c;
    cpu._r.m = 1;
}

void opcode_0x52(Z80& cpu)
{
    opcode_0x00(cpu);
    cpu._r.m = 1;
}

void opcode_0x53(Z80& cpu)
{
    cpu._r.d = cpu._r.e;
    cpu._r.m = 1;
}

void opcode_0x54(Z80& cpu)
{
    cpu._r.d = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x55(Z80& cpu)
{
    cpu._r.d = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x56(Z80& cpu)
{
    cpu._r.d = read_byte((((word) cpu._r.h) << 8) + cpu._r.l);
    cpu._r.m = 2;
}

void opcode_0x57(Z80& cpu)
{
    cpu._r.d = cpu._r.a;
    cpu._r.m = 1;
}

void opcode_0x58(Z80& cpu)
{
    cpu._r.e = cpu._r.b;
    cpu._r.m = 1;
}

void opcode_0x59(Z80& cpu)
{
    cpu._r.e = cpu._r.c;
    cpu._r.m = 1;
}

void opcode_0x5A(Z80& cpu)
{
    cpu._r.e = cpu._r.d;
    cpu._r.m = 1;
}

void opcode_0x5B(Z80& cpu)
{
    opcode_0x00(cpu);
    cpu._r.m = 1;
}

void opcode_0x5C(Z80& cpu)
{
    cpu._r.e = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x5D(Z80& cpu)
{
    cpu._r.e = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x5E(Z80& cpu)
{
    cpu._r.e = read_byte((((word) cpu._r.h) << 8) + cpu._r.l);
    cpu._r.m = 2;
}

void opcode_0x5F(Z80& cpu)
{
    cpu._r.e = cpu._r.a;
    cpu._r.m = 1;
}

void opcode_0x60(Z80& cpu)
{
    cpu._r.h = cpu._r.b;
    cpu._r.m = 1;
}

void opcode_0x61(Z80& cpu)
{
    cpu._r.h = cpu._r.c;
    cpu._r.m = 1;
}

void opcode_0x62(Z80& cpu)
{
    cpu._r.h = cpu._r.d;
    cpu._r.m = 1;
}

void opcode_0x63(Z80& cpu)
{
    cpu._r.h = cpu._r.e;
    cpu._r.m = 1;
}

void opcode_0x64(Z80& cpu)
{
    cpu._r.h = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x65(Z80& cpu)
{
    cpu._r.h = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x66(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu._r.h = read_byte(addr);
    cpu._r.m = 2;
}

void opcode_0x67(Z80& cpu)
{
    cpu._r.h = cpu._r.a;
    cpu._r.m = 1;
}

void opcode_0x68(Z80& cpu)
{
    cpu._r.l = cpu._r.b;
    cpu._r.m = 1;
}

void opcode_0x69(Z80& cpu)
{
    cpu._r.l = cpu._r.c;
    cpu._r.m = 1;
}

void opcode_0x6A(Z80& cpu)
{
    cpu._r.l = cpu._r.d;
    cpu._r.m = 1;
}

void opcode_0x6B(Z80& cpu)
{
    cpu._r.l = cpu._r.e;
    cpu._r.m = 1;
}

void opcode_0x6C(Z80& cpu)
{
    cpu._r.l = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x6D(Z80& cpu)
{
    cpu._r.l = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x6E(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu._r.l = read_byte(addr);
    cpu._r.m = 2;
}

void opcode_0x6F(Z80& cpu)
{
    cpu._r.l = cpu._r.a;
    cpu._r.m = 1;
}

void opcode_0x70(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.b);
    cpu._r.m = 2;
}

void opcode_0x71(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.c);
    cpu._r.m = 2;
}

void opcode_0x72(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.d);
    cpu._r.m = 2;
}

void opcode_0x73(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.e);
    cpu._r.m = 2;
}

void opcode_0x74(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.h);
    cpu._r.m = 2;
}

void opcode_0x75(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.l);
    cpu._r.m = 2;
}

void opcode_0x76(Z80& cpu)
{
//    std::cout << "ABORT! HALT" << std::endl;
//    std::raise(SIGABRT); // lel
}

void opcode_0x77(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    write_word(addr, cpu._r.a);
    cpu._r.m = 2;
}

void opcode_0x78(Z80& cpu)
{
    cpu._r.a = cpu._r.b;
    cpu._r.m = 1;
}

void opcode_0x79(Z80& cpu)
{
    cpu._r.a = cpu._r.c;
    cpu._r.m = 1;
}

void opcode_0x7A(Z80& cpu)
{
    cpu._r.a = cpu._r.d;
    cpu._r.m = 1;
}

void opcode_0x7B(Z80& cpu)
{
    cpu._r.a = cpu._r.e;
    cpu._r.m = 1;
}

void opcode_0x7C(Z80& cpu)
{
    cpu._r.a = cpu._r.h;
    cpu._r.m = 1;
}

void opcode_0x7D(Z80& cpu)
{
    cpu._r.a = cpu._r.l;
    cpu._r.m = 1;
}

void opcode_0x7E(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu._r.a = read_byte(addr);
    cpu._r.m = 2;
}

void opcode_0x7F(Z80& cpu)
{
    opcode_0x00(cpu);
}

void opcode_0x80(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.b);
    cpu._r.m = 1;
}

void opcode_0x81(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.c);
    cpu._r.m = 1;
}

void opcode_0x82(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.d);
    cpu._r.m = 1;
}

void opcode_0x83(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.e);
    cpu._r.m = 1;
}

void opcode_0x84(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.h);
    cpu._r.m = 1;
}

void opcode_0x85(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.l);
    cpu._r.m = 1;
}

void opcode_0x86(Z80& cpu)
{
    cpu.add(cpu._r.a, read_byte(((word) cpu._r.h) >> 8 + cpu._r.l));
    cpu._r.m = 4;
}

void opcode_0x87(Z80& cpu)
{
    opcode_0x00(cpu);
    cpu._r.m = 1;
}

void opcode_0x88(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.b + cpu.is_carry());
    cpu._r.m = 2;
}

void opcode_0x89(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.c + cpu.is_carry());
    cpu._r.m = 2;
}

void opcode_0x8A(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.d + cpu.is_carry());
    cpu._r.m = 2;
}

void opcode_0x8B(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.e + cpu.is_carry());
    cpu._r.m = 2;
}

void opcode_0x8C(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.h + cpu.is_carry());
    cpu._r.m = 2;
}

void opcode_0x8D(Z80& cpu)
{
    cpu.add(cpu._r.a, cpu._r.l + cpu.is_carry());
    cpu._r.m = 2;
}

void opcode_0x8E(Z80& cpu)
{
    cpu.add(cpu._r.a, read_byte(((word) cpu._r.h) >> 8 + cpu._r.l) + cpu.is_carry());
    cpu._r.m = 5;
}

void opcode_0x8F(Z80& cpu)
{
    opcode_0x00(cpu);
    cpu._r.m = 1;
}

void opcode_0x90(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.b);
    cpu._r.m = 1;
}

void opcode_0x91(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.c);
    cpu._r.m = 1;
}

void opcode_0x92(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.d);
    cpu._r.m = 1;
}

void opcode_0x93(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.e);
    cpu._r.m = 1;
}

void opcode_0x94(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.h);
    cpu._r.m = 1;
}

void opcode_0x95(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.l);
    cpu._r.m = 1;
}

void opcode_0x96(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu.sub(cpu._r.a, read_byte(addr));
    cpu._r.m = 2;
}

void opcode_0x97(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.a);
    cpu._r.m = 1;
}

void opcode_0x98(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.b + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x99(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.c + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x9A(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.d + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x9B(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.e + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x9C(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.h + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x9D(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.l + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x9E(Z80& cpu)
{
    word addr = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu.sub(cpu._r.a, read_byte(addr) + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0x9F(Z80& cpu)
{
    cpu.sub(cpu._r.a, cpu._r.a + (byte)(cpu.is_carry()));
    cpu._r.m = 1;
}

void opcode_0xA0(Z80& cpu)
{
    cpu.and_reg(cpu._r.b);
}

void opcode_0xA1(Z80& cpu)
{
    cpu.and_reg(cpu._r.c);
}

void opcode_0xA2(Z80& cpu)
{
    cpu.and_reg(cpu._r.d);
}

void opcode_0xA3(Z80& cpu)
{
    cpu.and_reg(cpu._r.e);
}

void opcode_0xA4(Z80& cpu)
{
    cpu.and_reg(cpu._r.h);
}

void opcode_0xA5(Z80& cpu)
{
    cpu.and_reg(cpu._r.l);
}

void opcode_0xA6(Z80& cpu)
{
    cpu.and_reg(read_byte((((word)cpu._r.h) << 8) + cpu._r.l));
}

void opcode_0xA7(Z80& cpu)
{
    cpu.and_reg(cpu._r.a);
}

void opcode_0xA8(Z80& cpu)
{
    cpu.xor_reg(cpu._r.b);
}

void opcode_0xA9(Z80& cpu)
{
    cpu.xor_reg(cpu._r.c);
}

void opcode_0xAA(Z80& cpu)
{
    cpu.xor_reg(cpu._r.d);
}

void opcode_0xAB(Z80& cpu)
{
    cpu.xor_reg(cpu._r.e);
}

void opcode_0xAC(Z80& cpu)
{
    cpu.xor_reg(cpu._r.h);
}

void opcode_0xAD(Z80& cpu)
{
    cpu.xor_reg(cpu._r.l);
}

void opcode_0xAE(Z80& cpu)
{
    cpu.xor_reg(read_byte((((word)cpu._r.h) << 8) + cpu._r.l));
}

void opcode_0xAF(Z80& cpu)
{
    cpu.xor_reg(cpu._r.a);
}

void opcode_0xB0(Z80& cpu)
{
    cpu.or_reg(cpu._r.b);
}

void opcode_0xB1(Z80& cpu)
{
    cpu.or_reg(cpu._r.c);
}

void opcode_0xB2(Z80& cpu)
{
    cpu.or_reg(cpu._r.d);
}

void opcode_0xB3(Z80& cpu)
{
    cpu.or_reg(cpu._r.e);
}

void opcode_0xB4(Z80& cpu)
{
    cpu.or_reg(cpu._r.h);
}

void opcode_0xB5(Z80& cpu)
{
    cpu.or_reg(cpu._r.l);
}

void opcode_0xB6(Z80& cpu)
{
    cpu.or_reg(read_byte((((word)cpu._r.h) << 8) + cpu._r.l));
}

void opcode_0xB7(Z80& cpu)
{
    cpu.or_reg(cpu._r.a);
}

void opcode_0xB8(Z80& cpu)
{
    cpu.compare(cpu._r.b);
}

void opcode_0xB9(Z80& cpu)
{
    cpu.compare(cpu._r.c);
}

void opcode_0xBA(Z80& cpu)
{
    cpu.compare(cpu._r.d);
}

void opcode_0xBB(Z80& cpu)
{
    cpu.compare(cpu._r.e);
}

void opcode_0xBC(Z80& cpu)
{
    cpu.compare(cpu._r.h);
}

void opcode_0xBD(Z80& cpu)
{
    cpu.compare(cpu._r.l);
}

void opcode_0xBE(Z80& cpu)
{
    cpu.compare(read_byte((((word)cpu._r.h) << 8) + cpu._r.l));
}

void opcode_0xBF(Z80& cpu)
{
    cpu.compare(cpu._r.a);
}

void opcode_0xC0(Z80& cpu)
{
    if(!cpu.is_zero())
        cpu.ret();
}

void opcode_0xC1(Z80& cpu)
{
    cpu.pop(cpu._r.b, cpu._r.c);
}

void opcode_0xC3(Z80& cpu)
{
    cpu._r.pc = read_word(cpu._r.pc);
    cpu._r.m = 3;
}

void opcode_0xC2(Z80& cpu)
{
    if(!cpu.is_zero())
        opcode_0xC3(cpu);
    else cpu._r.pc++;
}

void opcode_0xC4(Z80& cpu)
{
    if(!cpu.is_zero())
        cpu.call();
}

void opcode_0xC5(Z80& cpu)
{
    cpu.push((((word) cpu._r.b) << 8) + cpu._r.c);
}

void opcode_0xC6(Z80& cpu)
{
    cpu.add(cpu._r.a, read_byte(cpu._r.pc++));
    cpu._r.m = 2;
}

void opcode_0xC7(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0;
}

void opcode_0xC8(Z80& cpu)
{
    if(cpu.is_zero())
        cpu.ret();
}

void opcode_0xC9(Z80& cpu)
{
    cpu.ret();
}

void opcode_0xCA(Z80& cpu)
{
    if(cpu.is_zero())
        opcode_0xC3(cpu);
    else cpu._r.pc++;
}

void opcode_0xCC(Z80& cpu)
{
    if(cpu.is_zero())
        cpu.call();
}

void opcode_0xCD(Z80& cpu)
{
    cpu.call();
}

void opcode_0xCE(Z80& cpu)
{
    cpu.add(cpu._r.a, read_byte(cpu._r.pc++) + cpu.is_carry());
    cpu._r.m = 4;
}

void opcode_0xCF(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x8;
}

void opcode_0xD0(Z80& cpu)
{
    if(!cpu.is_carry())
        cpu.ret();
    cpu._r.m = 2;
}

void opcode_0xD1(Z80& cpu)
{
    cpu.pop(cpu._r.d, cpu._r.e);
    cpu._r.m = 3;
}

void opcode_0xD2(Z80& cpu)
{
    if(!cpu.is_carry())
        opcode_0xC3(cpu);
    else cpu._r.pc++;
}

void opcode_0xD3(Z80& cpu)
{
    std::cout <<  "Invalid instruction (0xD3)";
    exit(-1);
}

void opcode_0xD4(Z80& cpu)
{
    if(!cpu.is_carry())
        cpu.call();
}

void opcode_0xD5(Z80& cpu)
{
    cpu.push((((word) cpu._r.d) << 8) + cpu._r.e);
}

void opcode_0xD6(Z80& cpu)
{
    cpu.sub(cpu._r.a, read_byte(cpu._r.pc++));
    cpu._r.m = 2;
}

void opcode_0xD7(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x10;
}

void opcode_0xD8(Z80& cpu)
{
    if(cpu.is_carry())
        cpu.ret();
    cpu._r.m = 2;
}

void opcode_0xD9(Z80& cpu)
{
    // TODO complete this, as this requires to enable interrupts
}

void opcode_0xDA(Z80& cpu)
{
    if(cpu.is_carry())
        opcode_0xC3(cpu);
    else cpu._r.pc++;
}

void opcode_0xDB(Z80& cpu)
{
    std::cout <<  "Invalid instruction 0xDB";
    exit(-1);
}

void opcode_0xDC(Z80& cpu)
{
    if(cpu.is_carry())
        cpu.call();
}

void opcode_0xDD(Z80& cpu)
{
    std::cout <<  "Invalid instruction 0xDD at " << std::hex << cpu._r.pc;
    exit(-1);
}

void opcode_0xDE(Z80& cpu)
{
    cpu.sub(cpu._r.a, read_byte(cpu._r.pc++) + cpu.is_carry());
    cpu._r.m = 4;
}

void opcode_0xDF(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x18;
    cpu._r.m = 3;
}

void opcode_0xE0(Z80& cpu)
{
    write_byte(cpu._r.a, (word) (0xFF00 + read_byte(cpu._r.pc++)));
    cpu._r.m = 2;
}

void opcode_0xE1(Z80& cpu)
{
    cpu.pop(cpu._r.h, cpu._r.l);
}

void opcode_0xE2(Z80& cpu)
{
    write_byte(cpu._r.a, (word) (0xFF00 + read_byte(cpu._r.c)));
    cpu._r.m = 2;
}

void opcode_0xE3(Z80& cpu)
{
    std::cout <<  "Invalid instruction (0xE3)";
    exit(-1);
}

void opcode_0xE4(Z80& cpu)
{
    std::cout <<  "Invalid instruction (0xE4)";
    exit(-1);
}

void opcode_0xE5(Z80& cpu)
{
    cpu.push((((word) cpu._r.h) << 8) + cpu._r.l);
}

void opcode_0xE6(Z80& cpu)
{
    cpu.and_reg(read_byte(cpu._r.pc++));
}

void opcode_0xE7(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x20;
    cpu._r.m = 3;
}

void opcode_0xE8(Z80& cpu)
{
    cpu.add(cpu._r.sp, (sbyte) read_byte(cpu._r.pc++));
    cpu._r.m = 4;
}

void opcode_0xE9(Z80& cpu)
{
    cpu._r.pc = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu._r.m = 2;
}

void opcode_0xEA(Z80& cpu)
{
    write_byte(cpu._r.a, read_word(cpu._r.pc));
    cpu._r.pc += 2;
    cpu._r.m = 2;
}

void opcode_0xEB(Z80& cpu)
{
    std::cout <<  "Invalid instruction (0xEB)";
    exit(-1);
}

void opcode_0xEC(Z80& cpu)
{
    std::cout <<  "Invalid instruction (0xEC)";
    exit(-1);
}

void opcode_0xED(Z80& cpu)
{
    std::cout <<  "Invalid instruction (0xED)";
    exit(-1);
}

void opcode_0xEE(Z80& cpu)
{
    cpu.xor_reg(read_byte(cpu._r.pc++));
}

void opcode_0xEF(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x28;
    cpu._r.m = 3;
}

void opcode_0xF0(Z80& cpu)
{
    cpu._r.a = read_byte((word) (0xFF00 + read_byte(cpu._r.pc++)));
    cpu._r.m = 2;
}

void opcode_0xF1(Z80& cpu)
{
    cpu.pop(cpu._r.a, cpu._r.f);
}

void opcode_0xF2(Z80& cpu)
{
    std::cout <<  "Invalid instruction 0xF2";
//    exit(-1);
}

void opcode_0xF3(Z80& cpu)
{
    std::cout <<  "Disable Interrupts is not implemented" << std::endl; // TODO
//    exit(-1);
}

void opcode_0xF4(Z80& cpu)
{
    std::cout <<  "Invalid instruction 0xF4";
//    exit(-1);
}

void opcode_0xF5(Z80& cpu)
{
    cpu.push((((word) cpu._r.a) << 8) + cpu._r.f);
}

void opcode_0xF6(Z80& cpu)
{
    cpu._r.a |= read_byte(cpu._r.pc++);
    cpu.reset_flags();
    cpu.set_zero(cpu._r.a == 0);
    cpu._r.m = 2;
}

void opcode_0xF7(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x30;
}

void opcode_0xF8(Z80& cpu)
{
    word sum = cpu._r.sp + (sbyte) read_byte(cpu._r.pc++);
    cpu._r.sp = sum;
    cpu._r.h = (byte) (sum << 8);
    cpu._r.l = (byte) sum;
    cpu._r.m = 2;
}

void opcode_0xF9(Z80& cpu)
{
    cpu._r.sp = (((word) cpu._r.h) << 8) + cpu._r.l;
    cpu._r.m = 3;
}

void opcode_0xFA(Z80& cpu)
{
    cpu._r.a = read_byte(cpu._r.pc);
    cpu._r.pc += 2;
    cpu._r.m = 2;
}

void opcode_0xFB(Z80& cpu)
{
    std::cout <<  "Enable interrupts not here yet"; // TODO
//    exit(-1);
}

void opcode_0xFC(Z80& cpu)
{
    std::cout <<  "Invalid instruction 0xFC" << std::endl;
//    exit(-1);
}

void opcode_0xFD(Z80& cpu)
{
    std::cout <<  "Invalid instruction 0xFD";
//    exit(-1);
}

void opcode_0xFE(Z80& cpu)
{
    cpu.compare(read_byte(cpu._r.pc++));
}

void opcode_0xFF(Z80& cpu)
{
    cpu.push((word) (cpu._r.pc));
    cpu._r.pc = 0x38;
    cpu._r.m = 3;
}

#endif //GBEMU_OPCODES_H
