#include <iostream>
#include "CPU.h"
#include "GUI.h"

Z80 cpu;
char* rom_file_name = (char *) "/home/shahar/CLionProjects/GBEMU/Tetris.gb";

void boot()
{
    cpu._r.pc = 0x100;
    cpu._r.sp = 0xFFFE;
    std::cout << "Registers are set" << std::endl;
    load_ROM(rom_file_name);
    std::cout << "ROM is loaded" << std::endl;
}

int main() {
    std::cout << "Welcome to Gameboy EMU" << std::endl << std::endl;
    boot();
//    create_window(160, 144);
//    while(1){
//        SDL_RenderPresent(renderer);
//    }

    return 0;
}