#include <stdio.h>
#include <SDL2/SDL.h>

#include "Utils.h"
#include "Window.h"
#include "Game.h"

void Update(Window* window, Game* game, InputManager* inputManager)
{
    UpdateGame(game, inputManager);

    ClearScreen(window);
    RenderGame(game);

    Display(window);
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Init Failed. Error : %s\n", SDL_GetError());
    }

    int width = 1280;
    int height = 720;

    Window* window = CreateWindow("Pong Game", width, height);
    Game game;

    InputManager inputManager;

    InitialiseGame(&game, window);

    uint8_t gameRunning = 1;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = HireTimeInSeconds();

    while (gameRunning == 1)
    {
        int startTicks = SDL_GetTicks();

        float newTime = HireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    gameRunning = 0;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    /**if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        inputManager->leftDown = true;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        inputManager->rightDown = true;
                    }**/
                }
                else if (event.type == SDL_MOUSEBUTTONUP)
                {
                    /**if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        inputManager->leftDown = false;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        inputManager->rightDown = false;
                    }**/
                }
                else if (event.type == SDL_MOUSEMOTION)
                {
                    inputManager.mouseX = event.motion.x;
                    inputManager.mouseY = event.motion.y;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    /**if (!(event.key.keysym.sym == SDLK_SPACE))
                    {
                        inputManager->keys[event.key.keysym.sym] = true;
                    }**/
                }
                else if (event.type == SDL_KEYUP)
                {
                    /**if (!(event.key.keysym.sym == SDLK_SPACE))
                    {
                        inputManager->keys[event.key.keysym.sym] = false;
                    }
                    else
                    {
                        inputManager->keys[event.key.keysym.sym] = !inputManager->keys[event.key.keysym.sym];
                    }**/
                }
            }

            accumulator -= timeStep;
        }

        Update(window, &game, &inputManager);

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / GetRefreshRate(window))
        {
            SDL_Delay(1000 / GetRefreshRate(window) - frameTicks);
        }
    }

    DestroyWindow(window);

    SDL_Quit();

    printf("Done\n");
    for(;;)
    return 0;
}
