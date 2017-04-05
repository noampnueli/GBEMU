#include "definitions.h"

#ifndef GBEMU_CPU_H
#define GBEMU_CPU_H

class Z80
{
public:
    typedef struct clock
    {
        byte m, t;
    } clock;

    typedef struct regs
    {
        byte a, b, c, d, e, h, l, f; // 8-bit registers
        word pc, sp; // 16-bit registers
        byte m, t;
    } r;

    regs _r = {}; // init struct members to 0
    clock clock = {};

};


#endif //GBEMU_CPU_H
