#include <iostream>
#include <zconf.h>
#include "CPU.h"
#include "GUI.h"
#include "opmap.h"
#include "GPU.h"

Z80 cpu;
GPU gpu;
char* rom_file_name = (char *) "Tetris.gb";


void print_registers()
{
    std::cout << "a: " << (unsigned int) cpu._r.a << " ";
    std::cout << "b: " << (unsigned int) cpu._r.b << std::endl;
    std::cout << "c: " << (unsigned int) cpu._r.c << " ";
    std::cout << "d: " << (unsigned int) cpu._r.d << std::endl;
    std::cout << "e: " << (unsigned int) cpu._r.e << " ";
    std::cout << "h: " << (unsigned int) cpu._r.h << std::endl;
    std::cout << "l: " << (unsigned int) cpu._r.l << " ";
    std::cout << "pc: " << (unsigned int) cpu._r.pc << std::endl;
    std::cout << "--------------------------------" << std::endl;
}
// TODO finish and test
void dispatcher()
{
    bool run = true;
    while(run)
    {
        byte op = read_byte(cpu._r.pc++);
        cpu._r.pc &= 0xFFFF; // TODO check if needed

//        printf("OPCODE: %x %x\n", op, cpu._r.pc);

        if(op == 0xCB)
        {
            byte extra = read_byte(cpu._r.pc++);
//            printf("extra OP: %x %x\n", extra, cpu._r.pc);
            extra_opmap[extra](cpu);
        }

        else
        {
            opmap[op](cpu);
        }

//        print_registers();
        cpu._clock.m += cpu._r.m; // add time to CPU clock
        cpu._clock.t += cpu._r.t;

        if(access_vram)
        {
            gpu.update_tile((word) (access_vram & 0x1000));
            access_vram = 0;
        }

        gpu.step(cpu);
    }
    std::cout << "bye?" << std::endl;
}

void boot()
{
    cpu._r.pc = 0x100;
    cpu._r.sp = 0xFFFE;
    std::cout << "[*] Registers are set" << std::endl;
    load_ROM(rom_file_name);
    std::cout << "[*] ROM is loaded" << std::endl << std::endl;
    dispatcher();
}

int main() {

    std::cout << "[*] Welcome to Gameboy EMU" << std::endl << std::endl;
    boot();

    return 0;
}