#ifndef GBEMU_MMU_H
#define GBEMU_MMU_H

#include <fstream>
#include "definitions.h"

#define MEM_SIZE 0xFFFF
#define ROM_BANK_0 0
#define ROM_BANK_1 0x4000
#define VRAM 0x8000
#define EXT_RAM 0xA000
#define INTERNAL_RAM 0xC000

byte memory[MEM_SIZE];

word access_vram = 0;

inline byte read_byte(word addr)
{
    if(addr > MEM_SIZE)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    return memory[addr];
}

inline word read_word(word addr)
{
    if(addr > MEM_SIZE)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    return (word) (memory[addr]) + (word) (memory[addr + 1] << 8); // little endian
}

void write_byte(byte data, word addr)
{
    if(addr > MEM_SIZE)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    if(addr > VRAM && addr < EXT_RAM)
        access_vram = addr;
    memory[addr] = data;
}

void write_word(word data, word addr)
{
    if(addr > MEM_SIZE - 1)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    if(addr > VRAM && addr < EXT_RAM)
        access_vram = addr;

    memory[addr] = (byte) (data);   // little endian once again
    memory[addr + 1] = (byte) (data >> 8);
}

void load_ROM(const char* file_name) // TODO: Test when time has come
{
    std::ifstream rom_file;
    rom_file.open(file_name);
    if(!rom_file.good())
        std::cout << "Can't find ROM" << std::endl;

    rom_file.read((char *) memory, VRAM); // file size is up to 2 ROM banks = up to the VRAM

    rom_file.close();
}


#endif //GBEMU_MMU_H
