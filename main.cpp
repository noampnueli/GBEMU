#include <iostream>
#include "CPU.h"
#include "GUI.h"
#include "opmap.h"

Z80 cpu;
char* rom_file_name = (char *) "Tetris.gb";

// TODO finish and test
void dispatcher()
{
    while(1)
    {
        byte op = read_byte(cpu._r.pc++);
        cpu._r.pc &= 0xFFFF; // TODO check if needed
        opmap[op](cpu);

        cpu._clock.m += cpu._r.m; // add time to CPU clock
        cpu._clock.t += cpu._r.t;
    }
}

void boot()
{
    cpu._r.pc = 0x100;
    cpu._r.sp = 0xFFFE;
    std::cout << "[*] Registers are set" << std::endl;
    load_ROM(rom_file_name);
    std::cout << "[*] ROM is loaded" << std::endl;
}

int main() {

    std::cout << "[*] Welcome to Gameboy EMU" << std::endl << std::endl;
    boot();
    opmap[0](cpu);

//    create_window(160, 144);
//    while(1){
//        SDL_RenderPresent(renderer);
//    }

    return 0;
}