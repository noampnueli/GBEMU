
#ifndef GBEMU_GUI_H
#define GBEMU_GUI_H

#include <SDL2/SDL.h>

SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;
SDL_Event event;

void create_window(const int width, const int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("GBEMU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_SHOWN);

    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

/**
 * set a pixel on the SDL windows
 * @param x x location
 * @param y y location
 * @param r red
 * @param g green
 * @param b blue
 * @param a alpha
 */
void setPixel(int x, int y, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

bool isUpArrow()
{
    SDL_PollEvent(&event);
    return (event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_UP);
}

bool isDownArrow()
{
    SDL_PollEvent(&event);
    return (event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_DOWN);
}

bool isRightArrow()
{
    SDL_PollEvent(&event);
    return (event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RIGHT);
}

bool isLeftArrow()
{
    SDL_PollEvent(&event);
    return (event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_LEFT);
}

#endif //GBEMU_GUI_H
