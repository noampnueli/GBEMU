//
// Created by bubz on 4/5/17.
//

#ifndef GBEMU_MMU_H
#define GBEMU_MMU_H

#include "definitions.h"

#define MEM_SIZE 0xFFFF

byte memory[MEM_SIZE];

byte read_byte(word addr)
{
    return memory[addr];
}

word read_word(word addr)
{
    return (word) memory[addr] + (word) (memory[addr + 1] << 8); // little endian
}

void write_byte(byte data, word addr)
{
    if(addr > MEM_SIZE)
        throw "Invalid memory access";
    memory[addr] = data;
}

void write_word(word data, word addr)
{
    if(addr > MEM_SIZE - 1)
        throw "Invalid memory access";
    memory[addr] = (byte) (data);   // little endian once again
    memory[addr + 1] = (byte) (data >> 8);
}


#endif //GBEMU_MMU_H
