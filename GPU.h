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

    byte tileset[tile_num][64];

    bool bgmap = 1;

    word scroll_x = 0;
    word scroll_y = 0;

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

    void render_line2()
    {
        word tile_data = 0;
        word background_memory = 0;
        bool unsig = true;

        byte scroll_y = read_byte(0xFF42);
        byte scroll_x = read_byte(0xFF43);
        byte window_x = read_byte(0xFF4A);
        byte window_y = (byte) (read_byte(0xFF4B) - 7);

        bool using_window = false;

        byte lcd_control = read_byte(0xFF40);

        if(lcd_control & 0x20)
        {
            if(read_byte(0xFF44) <= window_y)
                using_window = true;
        }

        if(lcd_control & 0x10)
            tile_data = VRAM;
        else
        {
            tile_data = 0x8800;
            unsig = false;
        }

        if(!using_window)
        {
            if(lcd_control & 0x8)
                background_memory = 0x9C00;
            else
                background_memory = 0x9800;
        }
        else
        {
            if(lcd_control & 0x40)
                background_memory = 0x9C00;
            else
                background_memory = 0x9800;
        }

        byte y_pos = 0;

        if(!using_window)
            y_pos = scroll_y + read_byte(0xFF44);
        else
            y_pos = read_byte(0xFF44) - window_y;

        byte tile_row = (byte) ((y_pos / 8) * 32);

        for(int pixel = 0; pixel < 160; pixel++)
        {
            byte x_pos = (byte) (pixel + scroll_x);

            if(using_window)
            {
                if(pixel >= window_x)
                    x_pos = (byte) (pixel - window_x);
            }

            word tile_col = (word) (x_pos / 8);

            sword tile_id;

            word tile_addr = background_memory + tile_row + tile_col;

            if(unsig)
                tile_id = read_byte(tile_addr);
            else
                tile_id = (sbyte) read_byte(tile_addr);

            word tile_location = tile_data;
            if(unsig)
                tile_location += tile_id * 16;
            else
                tile_location += (tile_id + 128) * 16;

            byte line = (byte) (y_pos % 8);
            line *= 2;

            byte data1 = read_byte(tile_location + line);
            byte data2 = read_byte((word) (tile_location + line + 1));

            int colour_bit = x_pos % 8;
            colour_bit -= 7;
            colour_bit *= -1;

            int colour_num = (data2 & colour_bit) >> colour_bit;

            color col = palette[colour_num];

            int finally = read_word(0xFF44);

            if(finally < 0 || finally > 143 || pixel < 0 || pixel > 159)
                continue;

            set_pixel(pixel, finally, col.red, col.green, col.blue, 255);
        }
        render();
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

        map_offset += (((line + scroll_y) & 0xFF) >> 3) << 5;

        word line_offset = scroll_x >> 3;

        word y = (word) ((line + scroll_y) & 7);
        word x = (word) (scroll_x & 7);

        word tile = read_byte((word) (VRAM + map_offset + line_offset));
//        std::cout << "tile #" << std::hex << tile << std::endl;

//        print_tile(tile);

        word pixel_offset = (word) (line * width);

//        if(bgmap && tile < 128)
//        {
//            tile += 256;
//        }

        for(byte i = 0; i < 160; i++)
        {
            color c = palette[tileset[tile][y * 8 + x]];

            set_pixel(pixel_offset % width, pixel_offset / (width - 1), c.red, c.green, c.blue, 255);
            pixel_offset++;
//            std::cout << "pixel at (" << canvas_offset % width << ", " << canvas_offset / (width - 1) << ")" << std::endl;
//            std::cout << "(" << c.red << ", " << c.green << ", " << c.blue << std::endl;
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
        render();
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

                if(line == height - 1) // End of screen! Time for vblank
                {
                    mode = 1;
//                    draw_frame();
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
