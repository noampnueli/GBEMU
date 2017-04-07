#include "opcodes.h"

#ifndef GBEMU_OPMAP_H
#define GBEMU_OPMAP_H

void (*opmap[])(Z80&) =
{
    opcode_0x00,
    opcode_0x01
};

#endif //GBEMU_OPMAP_H
