
#ifndef GBEMU_GPU_H
#define GBEMU_GPU_H

#include <SDL2/SDL.h>

static typedef struct color
{
    int red;
    int green;
    int blue;

} color;

class GPU
{
private:
    color palette[4];

    void init_palette()
    {
        palette[0] = {255, 255, 255};
        palette[1] = {192, 192, 192};
        palette[2] = {96, 96, 96};
        palette[3] = {0, 0, 0};
    }

public:
    GPU()
    {
        init_palette();
    }
};
#endif //GBEMU_GPU_H
