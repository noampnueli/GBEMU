#ifndef GBEMU_OPMAP_H
#define GBEMU_OPMAP_H

#include "CPU.h"
#include "opcodes.h"

void (*opmap[])(Z80&) =
{
        opcode_0x00,
        opcode_0x01,
        opcode_0x02,
        opcode_0x03,
        opcode_0x04,
        opcode_0x05,
        opcode_0x06,
        opcode_0x07,
        opcode_0x08,
        opcode_0x09,
        opcode_0x0A,
        opcode_0x0B,
        opcode_0x0C,
        opcode_0x0D,
        opcode_0x0E,
        opcode_0x0F,
        opcode_0x10,
        opcode_0x11,
        opcode_0x12,
        opcode_0x13,
        opcode_0x14,
        opcode_0x15,
        opcode_0x16,
        opcode_0x17,
        opcode_0x18,
        opcode_0x19,
        opcode_0x1A,
        opcode_0x1B,
        opcode_0x1C,
        opcode_0x1D,
        opcode_0x1E,
        opcode_0x1F,
        opcode_0x20,
        opcode_0x21,
        opcode_0x22,
        opcode_0x23,
        opcode_0x24,
        opcode_0x25,
        opcode_0x26,
        opcode_0x27,
        opcode_0x28,
        opcode_0x29,
        opcode_0x2A,
        opcode_0x2B,
        opcode_0x2C,
        opcode_0x2D,
        opcode_0x2E,
        opcode_0x2F,
        opcode_0x30,
        opcode_0x31,
        opcode_0x32,
        opcode_0x33,
        opcode_0x34,
        opcode_0x35,
        opcode_0x36,
        opcode_0x37,
        opcode_0x38,
        opcode_0x39,
        opcode_0x3A,
        opcode_0x3B,
        opcode_0x3C,
        opcode_0x3D,
        opcode_0x3E,
        opcode_0x3F,
        opcode_0x40,
        opcode_0x41,
        opcode_0x42,
        opcode_0x43,
        opcode_0x44,
        opcode_0x45,
        opcode_0x46,
        opcode_0x47,
        opcode_0x48,
        opcode_0x49,
        opcode_0x4A,
        opcode_0x4B,
        opcode_0x4C,
        opcode_0x4D,
        opcode_0x4E,
        opcode_0x4F,
        opcode_0x50,
        opcode_0x51,
        opcode_0x52,
        opcode_0x53,
        opcode_0x54,
        opcode_0x55,
        opcode_0x56,
        opcode_0x57,
        opcode_0x58,
        opcode_0x59,
        opcode_0x5A,
        opcode_0x5B,
        opcode_0x5C,
        opcode_0x5D,
        opcode_0x5E,
        opcode_0x5F,
        opcode_0x60,
        opcode_0x61,
        opcode_0x62,
        opcode_0x63,
        opcode_0x64,
        opcode_0x65,
        opcode_0x66,
        opcode_0x67,
        opcode_0x68,
        opcode_0x69,
        opcode_0x6A,
        opcode_0x6B,
        opcode_0x6C,
        opcode_0x6D,
        opcode_0x6E,
        opcode_0x6F,
        opcode_0x70,
        opcode_0x71,
        opcode_0x72,
        opcode_0x73,
        opcode_0x74,
        opcode_0x75,
        opcode_0x76,
        opcode_0x77,
        opcode_0x78,
        opcode_0x79,
        opcode_0x7A,
        opcode_0x7B,
        opcode_0x7C,
        opcode_0x7D,
        opcode_0x7E,
        opcode_0x7F,
        opcode_0x80,
        opcode_0x81,
        opcode_0x82,
        opcode_0x83,
        opcode_0x84,
        opcode_0x85,
        opcode_0x86,
        opcode_0x87,
        opcode_0x88,
        opcode_0x89,
        opcode_0x8A,
        opcode_0x8B,
        opcode_0x8C,
        opcode_0x8D,
        opcode_0x8E,
        opcode_0x8F,
        opcode_0x90,
        opcode_0x91,
        opcode_0x92,
        opcode_0x93,
        opcode_0x94,
        opcode_0x95,
        opcode_0x96,
        opcode_0x97,
        opcode_0x98,
        opcode_0x99,
        opcode_0x9A,
        opcode_0x9B,
        opcode_0x9C,
        opcode_0x9D,
        opcode_0x9E,
        opcode_0x9F,
        opcode_0xA0,
        opcode_0xA1,
        opcode_0xA2,
        opcode_0xA3,
        opcode_0xA4,
        opcode_0xA5,
        opcode_0xA6,
        opcode_0xA7,
        opcode_0xA8,
        opcode_0xA9,
        opcode_0xAA,
        opcode_0xAB,
        opcode_0xAC,
        opcode_0xAD,
        opcode_0xAE,
        opcode_0xAF,
        opcode_0xB0,
        opcode_0xB1,
        opcode_0xB2,
        opcode_0xB3,
        opcode_0xB4,
        opcode_0xB5,
        opcode_0xB6,
        opcode_0xB7,
        opcode_0xB8,
        opcode_0xB9,
        opcode_0xBA,
        opcode_0xBB,
        opcode_0xBC,
        opcode_0xBD,
        opcode_0xBE,
        opcode_0xBF,
        opcode_0xC0,
        opcode_0xC1,
        opcode_0xC2,
        opcode_0xC3,
        opcode_0xC4,
        opcode_0xC5,
        opcode_0xC6,
        opcode_0xC7,
        opcode_0xC8,
        opcode_0xC9,
        opcode_0xCA,
        opcode_0xCB,
        opcode_0xCC,
        opcode_0xCD,
        opcode_0xCE,
        opcode_0xCF,
        opcode_0xD0,
        opcode_0xD1,
        opcode_0xD2,
        opcode_0xD3,
        opcode_0xD4,
        opcode_0xD5,
        opcode_0xD6,
        opcode_0xD7,
        opcode_0xD8,
        opcode_0xD9,
        opcode_0xDA,
        opcode_0xDB,
        opcode_0xDC,
        opcode_0xDD,
        opcode_0xDE,
        opcode_0xDF,
        opcode_0xE0,
        opcode_0xE1,
        opcode_0xE2,
        opcode_0xE3,
        opcode_0xE4,
        opcode_0xE5,
        opcode_0xE6,
        opcode_0xE7,
        opcode_0xE8,
        opcode_0xE9,
        opcode_0xEA,
        opcode_0xEB,
        opcode_0xEC,
        opcode_0xED,
        opcode_0xEE,
        opcode_0xEF,
        opcode_0xF0,
        opcode_0xF1,
        opcode_0xF2,
        opcode_0xF3,
        opcode_0xF4,
        opcode_0xF5,
        opcode_0xF6,
        opcode_0xF7,
        opcode_0xF8,
        opcode_0xF9,
        opcode_0xFA,
        opcode_0xFB,
        opcode_0xFC,
        opcode_0xFD,
        opcode_0xFE,
        opcode_0xFF
};

#endif //GBEMU_OPMAP_H
