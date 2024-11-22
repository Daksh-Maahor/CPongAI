#include "Window.h"
#include <stdio.h>

Window* CreateWindow(const char* title, int width, int height)
{
    Window* window = (Window*) malloc(sizeof(Window));
    window->window = NULL;
    window->width = width;
    window->height = height;

    window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Window failed to init. Error : %s", SDL_GetError());
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return window;
}

int GetRefreshRate(Window* window)
{
    int displayIndex = SDL_GetWindowDisplayIndex(window->window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

void DestroyWindow(Window* window)
{
    SDL_DestroyWindow(window->window);
    SDL_DestroyRenderer(window->renderer);

    free(window);
}

void ClearScreen(Window* window)
{
    SDL_RenderClear(window->renderer);
}

void Display(Window* window)
{
    SDL_RenderPresent(window->renderer);
}

void FillRect(Window* window, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 0xFF);

    SDL_Rect rect = {x, y, w, h};

    SDL_RenderFillRect(window->renderer, &rect);
}
