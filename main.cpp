#include <iostream>
#include <zconf.h>
#include "CPU.h"
#include "GUI.h"
#include "opmap.h"
#include "GPU.h"

Z80 cpu;
GPU gpu;
char* rom_file_name = (char *) "Tennis.gb";


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

        printf("OPCODE: %x %x\n", op, cpu._r.pc - 1);
//        printf("register: %x\n", cpu._r.a);
        if(op == 0xCB)
        {
            byte extra = read_byte(cpu._r.pc++);
            printf("extra OP: %x %x\n", extra, cpu._r.pc - 1);
            extra_opmap[extra](cpu);
        }

        else
        {
            opmap[op](cpu);
        }
        if(cpu._r.pc > 0x3635)
        {
            printf("");
            printf("*b: %x *\n", cpu._r.b);
            printf("");
        }

//        print_registers();
        cpu._clock.m += cpu._r.m; // add time to CPU clock
        cpu._clock.t += cpu._r.t;

        if(update_tile_address)
        {
            gpu.update_tile((word) (update_tile_address));
//            printf("VRAM OP: %x %x\n", op, update_tile_address);
            update_tile_address = 0;
        }

        gpu.control = gpu_control;
        gpu.scroll_x = gpu_scroll_x;
        gpu.scroll_y = gpu_scroll_y;
        gpu_line = gpu.line;

        gpu.step(cpu);
//        usleep(100);
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