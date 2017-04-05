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
    clock _clock = {};

    bool isZero()
    {
        return (_r.f & 0x80) > 0; // remove non-related bits, check if zero is on
    }

    void setZero(bool state)
    {
        if(isZero() != state) // if the desired state isn't the current, flip the flag value
            _r.f = _r.f ^ 0x80;
    }

    bool isOperation()
    {
        return (_r.f & 0x40) > 0;
    }

    void setOperation(bool state)
    {
        if(isOperation() != state)
            _r.f = _r.f ^ 0x40;
    }

    bool isHalfCarry()
    {
        return (_r.f & 0x20) > 0;
    }

    void setHalfCarry(bool state)
    {
        if(isHalfCarry() != state)
            _r.f = _r.f ^ 0x20;
    }

    bool isCarry()
    {
        return (_r.f & 0x10) > 0;
    }

    void setCarry(bool state)
    {
        if(isCarry() != state)
            _r.f = _r.f ^ 0x10;
    }

};


#endif //GBEMU_CPU_H
