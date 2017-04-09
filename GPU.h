#ifndef GBEMU_GPU_H
#define GBEMU_GPU_H

#include <iostream>
#include "GUI.h"
#include "CPU.h"
#include "MMU.h"

#define height 144
#define width 160

#define tile_num 384

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

    byte tileset[tile_num][64];

    bool bgmap;

    word scroll_x = 0;
    word scroll_y = 0;

    void init_palette()
    {
        palette[0] = {255, 255, 255};
        palette[1] = {192, 192, 192};
        palette[2] = {96, 96, 96};
        palette[3] = {0, 0, 0};
    }

    void draw_frame()
    {
//        for(word i = 0; i < height * width; i++)
//        {
//            color c = palette[frame_buffer[i]]; // TODO: implement actual way to find the colour
//            set_pixel(i % width, i / (width - 1), c.red, c.green, c.blue, 1);
//        }
    }

    void render_line()
    {
//        for(word i = (word) (VRAM + (line * width)); i < VRAM + (line * width) + width; i++)
//        {
//            frame_buffer[i - VRAM] = read_byte(i);
//        }
        word map_offset = 0;
        if(bgmap)
            map_offset = 0x1C00;
        else
            map_offset = 0x1800;

        map_offset += ((line + scroll_y) & 0xFF) >> 3;

        word line_offset = scroll_x >> 3;

        word y = (word) ((line + scroll_y) & 7);
        word x = (word) (scroll_x & 7);

        byte tile = read_byte((word) (VRAM + map_offset + line_offset));

        if(bgmap && tile < 128)
            tile += 256;

        for(byte i = 0; i < 160; i++)
        {
            color c = palette[tileset[tile][y * 8 + x]];

            set_pixel(x, y, c.red, c.green, c.blue, 1);

            x++;

            if(x == 8)
            {
                x = 0;
                line_offset = (word) ((line_offset + 1) & 31);
                tile = read_byte((word) (VRAM + line_offset + map_offset));

                if(bgmap && tile < 128)
                    tile += 256;
            }
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

    void update_tile(word addr)
    {
        // Get base address
        addr &= 0x1FFE;

        word tile = (word) ((addr >> 4) & 511);
        byte y = (byte) ((addr >> 1) & 7);
        byte sx;

        for(byte x = 0; x < 8; x++)
        {
            // Get bit index
            sx = (byte) (1 << (7 - x));

            byte lower = read_byte((word) (VRAM + addr)) & sx;
            byte upper = read_byte((word) (VRAM + addr + 1) & sx);

            if(upper) upper = 2;

            tileset[tile][y * 8 + x] = lower + upper;
        }
    }

    void step(Z80& cpu)
    {
        clock += cpu._r.m;
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
                render_line();
            }
        }
    }
};
#endif //GBEMU_GPU_H
