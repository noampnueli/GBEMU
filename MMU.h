#ifndef GBEMU_MMU_H
#define GBEMU_MMU_H

#include <fstream>
#include "definitions.h"
#include "GUI.h"

#define MEM_SIZE 0xFFFF
#define ROM_BANK_0 0
#define ROM_BANK_1 0x4000
#define VRAM 0x8000
#define EXT_RAM 0xA000
#define INTERNAL_RAM 0xC000
#define OAM 0xFE00

byte memory[MEM_SIZE] = {0};

word update_tile_address = 0;

byte gpu_control = 0;
word gpu_scroll_x = 0;
word gpu_scroll_y = 0;
byte gpu_line = 0;

static byte get_io_data()
{
    SDL_PollEvent(&event);

    byte data = 0;

    if(event.type == SDL_KEYDOWN)
        switch(event.key.keysym.sym)
        {
            case SDLK_DOWN:
                data &= (0x8 | 0x20);
                break;
            case SDLK_d: // Start
                data &= (0x8 | 0x10);
                break;
            case SDLK_UP:
                data &= (0x4 | 0x20);
                break;
            case SDLK_f: // Select
                data &= (0x4 | 0x10);
                break;
            case SDLK_LEFT:
                data &= (0x2 | 0x20);
                break;
            case SDLK_b:
                data &= (0x2 | 0x10);
                break;
            case SDLK_RIGHT:
                data &= (0x1 | 0x20);
                break;
            case SDLK_a:
                data &= (0x1 | 0x10);
                break;
            default:
                break;
        }

    return data;
}

inline byte read_byte(word addr)
{
    if(addr > MEM_SIZE)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    if(addr == 0xFF40) return gpu_control;
    else if(addr == 0xFF42) return (byte) gpu_scroll_x;
    else if(addr == 0xFF43) return (byte) gpu_scroll_y;
    else if(addr == 0xFF44) return gpu_line;

    return memory[addr];
}

inline word read_word(word addr)
{
    if(addr > MEM_SIZE)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    if(addr == 0xFF40) return gpu_control;
    else if(addr == 0xFF42) return gpu_scroll_x;
    else if(addr == 0xFF43) return gpu_scroll_y;
    else if(addr == 0xFF44) return gpu_line;

    return (word) (memory[addr]) | (word) (memory[addr + 1] << 8); // little endian
}

void write_byte(byte data, word addr)
{
    if(addr > MEM_SIZE)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

    if(addr >= VRAM && addr < EXT_RAM) {
        if(addr <= 0x97ff)
            update_tile_address = addr;
    }

    if(addr == 0xFF40) gpu_control = (byte) data;
    else if(addr == 0xFF42) gpu_scroll_x = (byte) data;
    else if(addr == 0xFF43) gpu_scroll_y = (byte) data;

    // Joypad I/O
    if(addr == 0xFF00)
    {
//        std::cout << "I/O party!" << std::endl;
        // Is scan requested
        if(!(data & 0x10) || !(data & 0x20))
        {
            data = get_io_data();
        }
    }

    memory[addr] = data;
}

void write_word(word data, word addr)
{
    if(addr > MEM_SIZE - 1)
    {
        std::cout << "Invalid memory access" << std::endl;
        exit(-1);
    }

//    update_tile_address = (addr & 0xF000) == 0x9000 ? addr : (word) 0;
    if(addr >= VRAM && addr < EXT_RAM) {
        if(addr <= 0x97ff)
            update_tile_address = addr;
    }

    if(addr == 0xFF40) gpu_control = (byte) data;
    else if(addr == 0xFF42) gpu_scroll_x = (byte) data;
    else if(addr == 0xFF43) gpu_scroll_y = (byte) data;

    memory[addr] = (byte) (data);   // little endian once again
    memory[addr + 1] = (byte) (data >> 8);
}

void load_ROM(const char* file_name)
{
    std::ifstream rom_file;
    rom_file.open(file_name);
    if(!rom_file.good())
        std::cout << "Can't find ROM" << std::endl;

    rom_file.read((char *) memory, VRAM); // file size is up to 2 ROM banks = up to the VRAM

    rom_file.close();
}


#endif //GBEMU_MMU_H
