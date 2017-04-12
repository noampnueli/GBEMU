#ifndef GBEMU_GPU_H
#define GBEMU_GPU_H

#include <iostream>
#include "GUI.h"
#include "CPU.h"
#include "MMU.h"

#define screen_height 144
#define screen_width 160

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

    byte tileset[tile_num][64];

    void init_palette()
    {
        palette[0] = {255, 255, 255};
        palette[1] = {192, 192, 192};
        palette[2] = {96, 96, 96};
        palette[3] = {0, 0, 0};
    }

    void print_tile(word tile)
    {
        for(int i = 0; i < 64; i++)
        {
            std::cout << " 0x" << std::hex << (int) tileset[tile][i] << " ";
            if(i % 9 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
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
        if(control & (1 << 3))
            map_offset = 0x1C00;
        else
            map_offset = 0x1800;

        map_offset += (((line + scroll_y) & 0xFF) >> 3) << 5;

        word line_offset = scroll_x >> 3;

        word y = (word) ((line + scroll_y) & 7);
        word x = (word) (scroll_x & 7);

        word tile = read_word((word) (VRAM + map_offset + line_offset - 1));
//        std::cout << "tile #" << std::hex << tile << std::endl;

//        print_tile(tile);

        word pixel_offset = (word) (line * screen_width);

        if(control & (1 << 3) && tile < 128)
        {
            tile += 256;
        }

        for(byte i = 0; i < 160; i++)
        {
            color c = palette[tileset[tile][y * 8 + x]];

            set_pixel(pixel_offset % screen_width, pixel_offset / (screen_width - 1), c.red, c.green, c.blue, 255);
            pixel_offset++;
//            std::cout << "pixel at (" << canvas_offset % width << ", " << canvas_offset / (width - 1) << ")" << std::endl;
//            std::cout << "(" << c.red << ", " << c.green << ", " << c.blue << std::endl;
            x++;

            if(x == 8)
            {
                x = 0;
                line_offset = (word) ((line_offset + 1) & 31);
                tile = read_byte((word) (VRAM + line_offset + map_offset));

                if(control & (1 << 3) && tile < 128)
                    tile += 256;
            }
        }
        render();
    }

    int mode;
    int clock;

public:
    // GPU control registers
    byte control = 0;
    word scroll_x = 0;
    word scroll_y = 0;
    byte line = 0;

    /*
     *  0 = Hblank
     *  1 = Vblank
     *  2 = Scan OAM
     *  3 = Scan VRAM
     */
    GPU()
    {
        init_palette();
        mode = 2;
        clock = 0;
        line = 0;

        create_window(screen_width, screen_height);
    }

    void update_tile(word addr)
    {
        // Get base address
//        std::cout << addr << std::endl;
        addr &= 0x1FFE;

        word tile = (word) ((addr >> 4) & 511);
        byte y = (byte) ((addr >> 1) & 7);
        byte sx;

        for(byte x = 0; x < 8; x++)
        {
            // Get bit index
            sx = (byte) (1 << (7 - x));

            byte lower = (byte) ((read_byte((word) (VRAM + addr)) & sx) ? 1 : 0);
            byte upper = (byte) ((read_byte((word) (VRAM + addr + 1)) & sx) ? 2 : 0);

            tileset[tile][y * 8 + x] = (lower + upper);
        }
//        std::cout << tile << std::endl;
//        print_tile(tile);
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

                if(line == screen_height - 1) // End of screen! Time for vblank
                {
                    mode = 1;
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

                line++;

                if(line > 153)
                {
                    line = 0;
                    mode = 2;
                }
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
