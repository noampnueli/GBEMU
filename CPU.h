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

    void add(byte& reg1, byte reg2)
    {
        reset_flags();
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
        reset_flags();
        if ((((reg1 & 0xFF) + (reg2 & 0xFF)) & 0x10) == 0x10)
            set_half_carry(1);
        if (reg1 > 0 && reg2 > (0xFF - reg1))
            set_carry(1);

        reg1 += reg2;

        if (reg1 == 0)
            set_zero(1);
        set_operation(0);
    }

    void add(byte& high, byte& low, word value)
    {
        reset_flags();
        word hl = ((word) high << 8) + (word) low;
        hl += value;
        high = (byte) ((hl >> 8) & 0xFF);
        low = (byte) (hl & 0xFF);
        if ((((hl & 0xFF) + (value & 0xFF)) & 0x10) == 0x10)
            set_half_carry(1);
        if (hl > 0 && value > (0xFF - hl))
            set_carry(1);
        set_zero(hl == 0);
        _r.m = 3;
    }

    void sub(byte& high, byte& low, word value)
    {
        reset_flags();

        word hl = (((word) high) << 8) + (word) low;
        hl -= value;

        if(hl == 0)
            set_zero(1);

        high = (byte) ((hl >> 8) & 0xFF);
        low = (byte) (hl & 0xFF);
    }

    void sub(byte& reg1, byte reg2)
    {
        reset_flags();
        if (reg1 < 0 && reg2 > (255 + reg1))
            set_carry(1);

        reg1 -= reg2;

        if (reg1 == 0)
            set_zero(1);
        set_operation(1);
    }

    void sub(word& reg1, word reg2)
    {
        reset_flags();
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
        _r.m = 1;
    }

    void or_reg(byte n)
    {
        _r.a |= n;
        reset_flags();
        if (_r.a == 0) {
            set_zero(1);
        }
        _r.m = 1;
    }

    void and_reg(byte n)
    {
        _r.a &= n;
        reset_flags();
        if (_r.a == 0) {
            set_zero(1);
        }
        set_half_carry(1);
        _r.m = 1;
    }

    void RR(byte& reg, bool carry)
    {
        byte carr = (byte) (reg & 0x01);
        if(carry)
            set_carry(carr);
        set_operation(0);
        set_half_carry(0);
        reg = (reg >> 1) + carr;
        if(reg == 0)
            set_zero(1);
        _r.m = 1;
    }

    void SLA(byte& reg)
    {
        byte tmp = reg;
        reg = (sbyte) reg << 1;
        if(reg == 0)
            set_zero(1);
        set_half_carry(0);
        set_operation(0);
        set_carry(tmp & 0x80);
        _r.m = 1;
    }

    void SRA(byte& reg)
    {
        byte tmp = reg;
        reg = (sbyte) reg >> 1;
        if(reg == 0)
            set_zero(1);
        set_half_carry(0);
        set_operation(0);
        set_carry(tmp & 0x01);
        _r.m = 1;
    }

    void SRL(byte& reg)
    {
        byte tmp = reg;
        reg = reg >> 1;
        if(reg == 0)
            set_zero(1);
        set_half_carry(0);
        set_operation(0);
        set_carry(tmp & 0x01);
        _r.m = 1;
    }

    void swap(byte& reg)
    {
        reset_flags();
        byte tmp = reg & 0xF;
        reg >>= 4;
        reg += tmp << 4;
        if(reg == 0)
            set_zero(1);
        _r.m = 1;
    }

    void RL(byte& reg, bool carry)
    {
        byte carr = (byte) (reg & 0xFF);
        if(carry)
            set_carry(carr);
        set_operation(0);
        set_half_carry(0);
        reg = (reg << 1) + carr;
        if(reg == 0)
            set_zero(1);
        _r.m = 1;
    }

    void BIT(byte reg, byte bit)
    {
        set_zero((reg & (1 << bit)) >> bit);
        set_operation(0);
        set_half_carry(1);
        _r.m = 1;
    }

    void RES(byte& reg, byte bit)
    {
        reg &= ~(1 << (bit - 1));
        _r.m = 1;
    }

    void SET(byte& reg, byte bit)
    {
        reg |= (1 << bit);
        _r.m = 1;
    }

    void compare(byte n)
    {
        set_zero(_r.a == n);
        set_operation(1);
        set_carry(_r.a > n);
        if((_r.a ^ (_r.a - n) ^ n) & 0x10)
            set_half_carry(1);
        _r.m = 2;
    }

    void ret()
    {
        _r.pc = read_word(_r.sp);
        _r.sp += 2;
        _r.m = 3;
    }

    void pop(byte& high, byte& low)
    {
        low = read_byte(_r.sp++);
        high = read_byte(_r.sp++);
        _r.m = 3;
    }

    void push(word nn)
    {
        _r.sp -= 2;
        write_word(nn, _r.sp);
        _r.m = 3;
    }

    void call()
    {
        push(_r.pc + 2);
        _r.pc = read_word(_r.pc);
        _r.m += 2;
    }

    void reset_flags()
    {
        _r.f = 0;
    }

    bool is_zero()
    {
        byte binval = _r.f & 0x80;
        bool is_zero = binval > 0;
        return is_zero; // remove non-related bits, check if zero is on
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
