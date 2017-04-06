#include <iostream>
#include "CPU.h"
#include "GUI.h"

Z80 cpu;

void boot()
{
    cpu._r.pc = 0x100;
    cpu._r.sp = 0xFFFE;
}

int main() {
    std::cout << "Welcome to Gameboy EMU" << std::endl;
//    create_window(160, 144);
//    while(1){
//        SDL_RenderPresent(renderer);
//    }

    return 0;
}