#ifndef GBEMU_GPU_H
#define GBEMU_GPU_H

#include <iostream>
#include "GUI.h"
#include "CPU.h"
#include "MMU.h"

#define height 144
#define width 160

class GPU
{
private:
    typedef struct color
    {
        int red;
        int green;
        int blue;

    } color;

    color palette[4];

    byte frame_buffer[height * width];

    void init_palette()
    {
        palette[0] = {255, 255, 255};
        palette[1] = {192, 192, 192};
        palette[2] = {96, 96, 96};
        palette[3] = {0, 0, 0};
    }

    void draw_frame()
    {
        for(word i = 0; i < height * width; i++)
        {
            color c = palette[frame_buffer[i]]; // TODO: implement actual way to find the colour
            set_pixel(i % width, i / (width - 1), c.red, c.green, c.blue, 1);
        }
    }

    void scan_line()
    {
        for(word i = (word) (VRAM + (line * width)); i < VRAM + (line * width) + width; i++)
        {
            frame_buffer[i] = read_byte(i);
        }
    }

    int mode;
    int clock;
    int line;

public:
    /*
     *  0 = Hblank
     *  1 = Vblank
     *  2 = Scan OAM
     *  3 = Scan VRAM
     */
    GPU()
    {
        init_palette();
        mode = 0;
        clock = 0;
        line = 0;

        create_window(width, height);
    }

    void step(Z80& cpu)
    {
        clock += cpu._r.t;
//        std::cout << clock << std::endl;

        // Hblank (new line)
        if(mode == 0)
        {
            // Check if num of clocks has passed
            if(clock >= 204)
            {
                clock = 0;
                line++;

                if(line == height - 1) // End of screen! Time for vblank
                {
                    mode = 1;
                    draw_frame();
                }
                else
                {
                    mode = 2;
                }
            }
        }
        // Vblank end of the ends
        else if(mode == 1)
        {
            if(clock >= 456)
            {
                clock = 0;
                line = 0;
                mode = 2;
            }
        }
        // Scan OAM
        else if(mode == 2)
        {
            if(clock >= 80)
            {
                clock = 0;
                mode = 3;
            }
        }
        // Scan VRAM
        else if(mode == 3)
        {
            if(clock >= 172)
            {
                clock = 0;
                mode = 0;

                scan_line();
            }
        }
    }
};
#endif //GBEMU_GPU_H
