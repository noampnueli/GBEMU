

#ifndef GBEMU_EXTRA_OPCODES_H
#define GBEMU_EXTRA_OPCODES_H

#include "CPU.h"

void ext_0x00(Z80& cpu)
{
    cpu.RL(cpu._r.b, 1);
}

void ext_0x01(Z80& cpu)
{
    cpu.RL(cpu._r.c, 1);
}

void ext_0x02(Z80& cpu)
{
    cpu.RL(cpu._r.d, 1);
}

void ext_0x03(Z80& cpu)
{
    cpu.RL(cpu._r.e, 1);
}

void ext_0x04(Z80& cpu)
{
    cpu.RL(cpu._r.h, 1);
}

void ext_0x05(Z80& cpu)
{
    cpu.RL(cpu._r.l, 1);
}

void ext_0x06(Z80& cpu)
{

}

void ext_0x07(Z80& cpu)
{
    cpu.RL(cpu._r.a, 1);
}

void ext_0x08(Z80& cpu)
{
    cpu.RR(cpu._r.b, 1);
}

void ext_0x09(Z80& cpu)
{
    cpu.RR(cpu._r.c, 1);
}

void ext_0x0A(Z80& cpu)
{
    cpu.RR(cpu._r.d, 1);
}

void ext_0x0B(Z80& cpu)
{
    cpu.RR(cpu._r.e, 1);
}

void ext_0x0C(Z80& cpu)
{
    cpu.RR(cpu._r.h, 1);
}

void ext_0x0D(Z80& cpu)
{
    cpu.RR(cpu._r.l, 1);
}

void ext_0x0E(Z80& cpu)
{

}

void ext_0x0F(Z80& cpu)
{
    cpu.RR(cpu._r.a, 1);
}

void ext_0x10(Z80& cpu)
{
    cpu.RL(cpu._r.b, 0);
}

void ext_0x11(Z80& cpu)
{
    cpu.RL(cpu._r.c, 0);
}

void ext_0x12(Z80& cpu)
{
    cpu.RL(cpu._r.d, 0);
}

void ext_0x13(Z80& cpu)
{
    cpu.RL(cpu._r.e, 0);
}

void ext_0x14(Z80& cpu)
{
    cpu.RL(cpu._r.h, 0);
}

void ext_0x15(Z80& cpu)
{
    cpu.RL(cpu._r.l, 0);
}

void ext_0x16(Z80& cpu)
{

}

void ext_0x17(Z80& cpu)
{
    cpu.RL(cpu._r.a, 0);
}

void ext_0x18(Z80& cpu)
{
    cpu.RR(cpu._r.b, 0);
}

void ext_0x19(Z80& cpu)
{
    cpu.RR(cpu._r.c, 0);
}

void ext_0x1A(Z80& cpu)
{
    cpu.RR(cpu._r.d, 0);
}

void ext_0x1B(Z80& cpu)
{
    cpu.RR(cpu._r.e, 0);
}

void ext_0x1C(Z80& cpu)
{
    cpu.RR(cpu._r.h, 0);
}

void ext_0x1D(Z80& cpu)
{
    cpu.RR(cpu._r.l, 0);
}

void ext_0x1E(Z80& cpu)
{

}

void ext_0x1F(Z80& cpu)
{
    cpu.RR(cpu._r.a, 0);
}

void ext_0x20(Z80& cpu)
{
    cpu.SLA(cpu._r.b);
}

void ext_0x21(Z80& cpu)
{
    cpu.SLA(cpu._r.c);
}

void ext_0x22(Z80& cpu)
{
    cpu.SLA(cpu._r.d);
}

void ext_0x23(Z80& cpu)
{
    cpu.SLA(cpu._r.e);
}

void ext_0x24(Z80& cpu)
{
    cpu.SLA(cpu._r.h);
}

void ext_0x25(Z80& cpu)
{
    cpu.SLA(cpu._r.l);
}

void ext_0x26(Z80& cpu)
{

}

void ext_0x27(Z80& cpu)
{
    cpu.SLA(cpu._r.a);
}

void ext_0x28(Z80& cpu)
{
    cpu.SRA(cpu._r.b);
}

void ext_0x29(Z80& cpu)
{
    cpu.SRA(cpu._r.c);
}

void ext_0x2A(Z80& cpu)
{
    cpu.SRA(cpu._r.d);
}

void ext_0x2B(Z80& cpu)
{
    cpu.SRA(cpu._r.e);
}

void ext_0x2C(Z80& cpu)
{
    cpu.SRA(cpu._r.h);
}

void ext_0x2D(Z80& cpu)
{
    cpu.SRA(cpu._r.l);
}

void ext_0x2E(Z80& cpu)
{

}

void ext_0x2F(Z80& cpu)
{
    cpu.SRA(cpu._r.a);
}

void ext_0x30(Z80& cpu)
{
    cpu.swap(cpu._r.b);
}

void ext_0x31(Z80& cpu)
{
    cpu.swap(cpu._r.c);
}

void ext_0x32(Z80& cpu)
{
    cpu.swap(cpu._r.d);
}

void ext_0x33(Z80& cpu)
{
    cpu.swap(cpu._r.e);
}

void ext_0x34(Z80& cpu)
{
    cpu.swap(cpu._r.h);
}

void ext_0x35(Z80& cpu)
{
    cpu.swap(cpu._r.l);
}

void ext_0x36(Z80& cpu)
{

}

void ext_0x37(Z80& cpu)
{
    cpu.swap(cpu._r.a);
}

void ext_0x38(Z80& cpu)
{
    cpu._r.b >>= 1;
    cpu._r.m = 1;
}

void ext_0x39(Z80& cpu)
{
    cpu._r.c >>= 1;
    cpu._r.m = 1;
}

void ext_0x3A(Z80& cpu)
{
    cpu._r.d >>= 1;
    cpu._r.m = 1;
}

void ext_0x3B(Z80& cpu)
{
    cpu._r.e >>= 1;
    cpu._r.m = 1;
}

void ext_0x3C(Z80& cpu)
{
    cpu._r.h >>= 1;
    cpu._r.m = 1;
}

void ext_0x3D(Z80& cpu)
{
    cpu._r.l >>= 1;
    cpu._r.m = 1;
}

void ext_0x3E(Z80& cpu)
{

}

void ext_0x3F(Z80& cpu)
{
    cpu._r.a >>= 1;
    cpu._r.m = 1;
}

void ext_0x40(Z80& cpu)
{

}

void ext_0x41(Z80& cpu)
{

}

void ext_0x42(Z80& cpu)
{

}

void ext_0x43(Z80& cpu)
{

}

void ext_0x44(Z80& cpu)
{

}

void ext_0x45(Z80& cpu)
{

}

void ext_0x46(Z80& cpu)
{

}

void ext_0x47(Z80& cpu)
{

}

void ext_0x48(Z80& cpu)
{

}

void ext_0x49(Z80& cpu)
{

}

void ext_0x4A(Z80& cpu)
{

}

void ext_0x4B(Z80& cpu)
{

}

void ext_0x4C(Z80& cpu)
{

}

void ext_0x4D(Z80& cpu)
{

}

void ext_0x4E(Z80& cpu)
{

}

void ext_0x4F(Z80& cpu)
{

}

void ext_0x50(Z80& cpu)
{

}

void ext_0x51(Z80& cpu)
{

}

void ext_0x52(Z80& cpu)
{

}

void ext_0x53(Z80& cpu)
{

}

void ext_0x54(Z80& cpu)
{

}

void ext_0x55(Z80& cpu)
{

}

void ext_0x56(Z80& cpu)
{

}

void ext_0x57(Z80& cpu)
{

}

void ext_0x58(Z80& cpu)
{

}

void ext_0x59(Z80& cpu)
{

}

void ext_0x5A(Z80& cpu)
{

}

void ext_0x5B(Z80& cpu)
{

}

void ext_0x5C(Z80& cpu)
{

}

void ext_0x5D(Z80& cpu)
{

}

void ext_0x5E(Z80& cpu)
{

}

void ext_0x5F(Z80& cpu)
{

}

void ext_0x60(Z80& cpu)
{

}

void ext_0x61(Z80& cpu)
{

}

void ext_0x62(Z80& cpu)
{

}

void ext_0x63(Z80& cpu)
{

}

void ext_0x64(Z80& cpu)
{

}

void ext_0x65(Z80& cpu)
{

}

void ext_0x66(Z80& cpu)
{

}

void ext_0x67(Z80& cpu)
{

}

void ext_0x68(Z80& cpu)
{

}

void ext_0x69(Z80& cpu)
{

}

void ext_0x6A(Z80& cpu)
{

}

void ext_0x6B(Z80& cpu)
{

}

void ext_0x6C(Z80& cpu)
{

}

void ext_0x6D(Z80& cpu)
{

}

void ext_0x6E(Z80& cpu)
{

}

void ext_0x6F(Z80& cpu)
{

}

void ext_0x70(Z80& cpu)
{

}

void ext_0x71(Z80& cpu)
{

}

void ext_0x72(Z80& cpu)
{

}

void ext_0x73(Z80& cpu)
{

}

void ext_0x74(Z80& cpu)
{

}

void ext_0x75(Z80& cpu)
{

}

void ext_0x76(Z80& cpu)
{

}

void ext_0x77(Z80& cpu)
{

}

void ext_0x78(Z80& cpu)
{

}

void ext_0x79(Z80& cpu)
{

}

void ext_0x7A(Z80& cpu)
{

}

void ext_0x7B(Z80& cpu)
{

}

void ext_0x7C(Z80& cpu)
{

}

void ext_0x7D(Z80& cpu)
{

}

void ext_0x7E(Z80& cpu)
{

}

void ext_0x7F(Z80& cpu)
{

}

void ext_0x80(Z80& cpu)
{

}

void ext_0x81(Z80& cpu)
{

}

void ext_0x82(Z80& cpu)
{

}

void ext_0x83(Z80& cpu)
{

}

void ext_0x84(Z80& cpu)
{

}

void ext_0x85(Z80& cpu)
{

}

void ext_0x86(Z80& cpu)
{

}

void ext_0x87(Z80& cpu)
{

}

void ext_0x88(Z80& cpu)
{

}

void ext_0x89(Z80& cpu)
{

}

void ext_0x8A(Z80& cpu)
{

}

void ext_0x8B(Z80& cpu)
{

}

void ext_0x8C(Z80& cpu)
{

}

void ext_0x8D(Z80& cpu)
{

}

void ext_0x8E(Z80& cpu)
{

}

void ext_0x8F(Z80& cpu)
{

}

void ext_0x90(Z80& cpu)
{

}

void ext_0x91(Z80& cpu)
{

}

void ext_0x92(Z80& cpu)
{

}

void ext_0x93(Z80& cpu)
{

}

void ext_0x94(Z80& cpu)
{

}

void ext_0x95(Z80& cpu)
{

}

void ext_0x96(Z80& cpu)
{

}

void ext_0x97(Z80& cpu)
{

}

void ext_0x98(Z80& cpu)
{

}

void ext_0x99(Z80& cpu)
{

}

void ext_0x9A(Z80& cpu)
{

}

void ext_0x9B(Z80& cpu)
{

}

void ext_0x9C(Z80& cpu)
{

}

void ext_0x9D(Z80& cpu)
{

}

void ext_0x9E(Z80& cpu)
{

}

void ext_0x9F(Z80& cpu)
{

}

void ext_0xA0(Z80& cpu)
{

}

void ext_0xA1(Z80& cpu)
{

}

void ext_0xA2(Z80& cpu)
{

}

void ext_0xA3(Z80& cpu)
{

}

void ext_0xA4(Z80& cpu)
{

}

void ext_0xA5(Z80& cpu)
{

}

void ext_0xA6(Z80& cpu)
{

}

void ext_0xA7(Z80& cpu)
{

}

void ext_0xA8(Z80& cpu)
{

}

void ext_0xA9(Z80& cpu)
{

}

void ext_0xAA(Z80& cpu)
{

}

void ext_0xAB(Z80& cpu)
{

}

void ext_0xAC(Z80& cpu)
{

}

void ext_0xAD(Z80& cpu)
{

}

void ext_0xAE(Z80& cpu)
{

}

void ext_0xAF(Z80& cpu)
{

}

void ext_0xB0(Z80& cpu)
{

}

void ext_0xB1(Z80& cpu)
{

}

void ext_0xB2(Z80& cpu)
{

}

void ext_0xB3(Z80& cpu)
{

}

void ext_0xB4(Z80& cpu)
{

}

void ext_0xB5(Z80& cpu)
{

}

void ext_0xB6(Z80& cpu)
{

}

void ext_0xB7(Z80& cpu)
{

}

void ext_0xB8(Z80& cpu)
{

}

void ext_0xB9(Z80& cpu)
{

}

void ext_0xBA(Z80& cpu)
{

}

void ext_0xBB(Z80& cpu)
{

}

void ext_0xBC(Z80& cpu)
{

}

void ext_0xBD(Z80& cpu)
{

}

void ext_0xBE(Z80& cpu)
{

}

void ext_0xBF(Z80& cpu)
{

}

void ext_0xC0(Z80& cpu)
{

}

void ext_0xC1(Z80& cpu)
{

}

void ext_0xC2(Z80& cpu)
{

}

void ext_0xC3(Z80& cpu)
{

}

void ext_0xC4(Z80& cpu)
{

}

void ext_0xC5(Z80& cpu)
{

}

void ext_0xC6(Z80& cpu)
{

}

void ext_0xC7(Z80& cpu)
{

}

void ext_0xC8(Z80& cpu)
{

}

void ext_0xC9(Z80& cpu)
{

}

void ext_0xCA(Z80& cpu)
{

}

void ext_0xCB(Z80& cpu)
{

}

void ext_0xCC(Z80& cpu)
{

}

void ext_0xCD(Z80& cpu)
{

}

void ext_0xCE(Z80& cpu)
{

}

void ext_0xCF(Z80& cpu)
{

}

void ext_0xD0(Z80& cpu)
{

}

void ext_0xD1(Z80& cpu)
{

}

void ext_0xD2(Z80& cpu)
{

}

void ext_0xD3(Z80& cpu)
{

}

void ext_0xD4(Z80& cpu)
{

}

void ext_0xD5(Z80& cpu)
{

}

void ext_0xD6(Z80& cpu)
{

}

void ext_0xD7(Z80& cpu)
{

}

void ext_0xD8(Z80& cpu)
{

}

void ext_0xD9(Z80& cpu)
{

}

void ext_0xDA(Z80& cpu)
{

}

void ext_0xDB(Z80& cpu)
{

}

void ext_0xDC(Z80& cpu)
{

}

void ext_0xDD(Z80& cpu)
{

}

void ext_0xDE(Z80& cpu)
{

}

void ext_0xDF(Z80& cpu)
{

}

void ext_0xE0(Z80& cpu)
{

}

void ext_0xE1(Z80& cpu)
{

}

void ext_0xE2(Z80& cpu)
{

}

void ext_0xE3(Z80& cpu)
{

}

void ext_0xE4(Z80& cpu)
{

}

void ext_0xE5(Z80& cpu)
{

}

void ext_0xE6(Z80& cpu)
{

}

void ext_0xE7(Z80& cpu)
{

}

void ext_0xE8(Z80& cpu)
{

}

void ext_0xE9(Z80& cpu)
{

}

void ext_0xEA(Z80& cpu)
{

}

void ext_0xEB(Z80& cpu)
{

}

void ext_0xEC(Z80& cpu)
{

}

void ext_0xED(Z80& cpu)
{

}

void ext_0xEE(Z80& cpu)
{

}

void ext_0xEF(Z80& cpu)
{

}

void ext_0xF0(Z80& cpu)
{

}

void ext_0xF1(Z80& cpu)
{

}

void ext_0xF2(Z80& cpu)
{

}

void ext_0xF3(Z80& cpu)
{

}

void ext_0xF4(Z80& cpu)
{

}

void ext_0xF5(Z80& cpu)
{

}

void ext_0xF6(Z80& cpu)
{

}

void ext_0xF7(Z80& cpu)
{

}

void ext_0xF8(Z80& cpu)
{

}

void ext_0xF9(Z80& cpu)
{

}

void ext_0xFA(Z80& cpu)
{

}

void ext_0xFB(Z80& cpu)
{

}

void ext_0xFC(Z80& cpu)
{

}

void ext_0xFD(Z80& cpu)
{

}

void ext_0xFE(Z80& cpu)
{

}

void ext_0xFF(Z80& cpu)
{

}


#endif //GBEMU_EXTRA_OPCODES_H
