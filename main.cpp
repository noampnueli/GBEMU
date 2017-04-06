#include <iostream>
#include "CPU.h"
#include "GUI.h"

int main() {
    std::cout << "Welcome to Gameboy EMU" << std::endl;
    Z80 cpu;
    create_window(160, 144);

    return 0;
}