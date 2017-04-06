#ifndef GBEMU_CPU_H
#define GBEMU_CPU_H

#include "definitions.h"
#include "MMU.h"

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
    } regs;

    regs _r = {}; // init struct members to 0
    clock _clock = {};

    void reset()
    {
        _r = {};
        _clock = {};
    }

    // TODO finish and test
    void dispatcher()
    {
        while(1)
        {
            byte op = read_byte(_r.pc++);
            // TODO execute function according to opcode
            _r.pc &= 65535; // TODO check if needed
            _clock.m += _r.m; // add time to CPU clock
            _clock.t += _r.t;
        }
    }

    void add(byte& reg1, byte reg2)
    {
        if ((((reg1 & 0x0F) + (reg2 & 0x0F)) & 0x10) == 0x10)
            set_half_carry(1);
        if (reg1 > 0 && reg2 > (0xFF - reg1))
            set_carry(1);

        reg1 += reg2;

        if (reg1 == 0)
            set_zero(1);
        set_operation(0);
    }

    void add(word& reg1, word reg2)
    {
        if ((((reg1 & 0xFF) + (reg2 & 0xFF)) & 0x10) == 0x10)
            set_half_carry(1);
        if (reg1 > 0 && reg2 > (0xFF - reg1))
            set_carry(1);

        reg1 += reg2;

        if (reg1 == 0)
            set_zero(1);
        set_operation(0);
    }

    void sub(byte& reg1, byte reg2)
    {
        if (reg1 < 0 && reg2 > (255 + reg1))
            set_carry(1);

        reg1 -= reg2;

        if (reg1 == 0)
            set_zero(1);
        set_operation(1);
    }

    void sub(word& reg1, word reg2)
    {
        if (reg1 < 0 && reg2 > (0xFF + reg1))
            set_carry(1);

        reg1 -= reg2;

        if (reg1 == 0)
            set_zero(1);
        set_operation(1);
    }

    void xor_reg(byte n)
    {
        _r.a ^= n;
        reset_flags();
        if (_r.a == 0) {
            set_zero(1);
        }
    }

    void or_reg(byte n)
    {
        _r.a |= n;
        reset_flags();
        if (_r.a == 0) {
            set_zero(1);
        }
    }

    void and_reg(byte n)
    {
        _r.a &= n;
        reset_flags();
        if (_r.a == 0) {
            set_zero(1);
        }
    }

    void reset_flags()
    {
        _r.f = 0;
    }

    bool is_zero()
    {
        return (_r.f & 0x80) > 0; // remove non-related bits, check if zero is on
    }

    void set_zero(bool state)
    {
        if(is_zero() != state) // if the desired state isn't the current, flip the flag value
            _r.f = _r.f ^ 0x80;
    }

    bool is_operation()
    {
        return (_r.f & 0x40) > 0;
    }

    void set_operation(bool state)
    {
        if(is_operation() != state)
            _r.f = _r.f ^ 0x40;
    }

    bool is_half_carry()
    {
        return (_r.f & 0x20) > 0;
    }

    void set_half_carry(bool state)
    {
        if(is_half_carry() != state)
            _r.f = _r.f ^ 0x20;
    }

    bool is_carry()
    {
        return (_r.f & 0x10) > 0;
    }

    void set_carry(bool state)
    {
        if(is_carry() != state)
            _r.f = _r.f ^ 0x10;
    }

};


#endif //GBEMU_CPU_H
