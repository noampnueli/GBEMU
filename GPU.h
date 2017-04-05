//
// Created by bubz on 4/5/17.
//

#ifndef GBEMU_GPU_H
#define GBEMU_GPU_H

#include <SDL2/SDL.h>

typedef struct color
{
    int red;
    int green;
    int blue;
    
} color;

color palette[4];

void init_palette()
{
    palette[0] = {255, 255, 255};
    palette[1] = {192, 192, 192};
    palette[2] = {96, 96, 96};
    palette[3] = {0, 0, 0};
}

#endif //GBEMU_GPU_H
