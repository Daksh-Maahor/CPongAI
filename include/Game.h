#ifndef GAME_H_
#define GAME_H_

#include "Window.h"
#include "Utils.h"
#include "AI.h"

#define PADDLE_HEIGHT(win) (win->height / 8)
#define PADDLE_WIDTH(win) (PADDLE_HEIGHT(win)/10)

#define BALL_SIZE(win) (PADDLE_WIDTH(win) * 2)

typedef struct
{
    Window* window;
    int x1;
    int x2;
    int y1;
    int y2;
    int ballX;
    int ballY;
    int ballVx;
    int ballVy;
    int p_width;
    int p_height;
    int ballSize;
    int y1Prev;
    int y2Prev;
    float v1;
    float v2;
    AI ai;
} Game;

void InitialiseGame(Game* game, Window* window);
void RenderGame(Game* game);
void UpdateGame(Game* game, InputManager* inputManager);
int MakeDecision(Game* game);

#endif
