//
// Created by bubz on 4/5/17.
//

#ifndef GBEMU_MMU_H
#define GBEMU_MMU_H

#include "definitions.h"

byte memory[0xFFFF];

byte read_byte(word addr)
{
    return memory[addr];
}

word read_word(word addr)
{
    return (word) memory[addr] + (word) (memory[addr + 1] << 8);
}


#endif //GBEMU_MMU_H
