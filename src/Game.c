#include "Game.h"
#include <stdio.h>

void InitialiseGame(Game* game, Window* window)
{
    game->window = window;
    game->p_width = PADDLE_WIDTH(window);
    game->p_height = PADDLE_HEIGHT(window);
    game->x1 = game->p_width * 4 + game->p_width / 2;
    game->x2 = window->width - game->p_width * 4 - game->p_width / 2;
    game->y1 = window->height / 2;
    game->y2 = game->y1;
    game->ballX = window->width / 2;
    game->ballY = window->height / 2;
    game->ballSize = BALL_SIZE(game->window);
    game->ballVx = AI_SPEED;
    game->ballVy = AI_SPEED;
    game->y1Prev = game->y1;
    game->y2Prev = game->y2;
    game->v1 = 0;
    game->v2 = 0;
    InitialiseAI(&(game->ai));
    //PrintAI(&(game->ai));
}

void RenderGame(Game* game)
{
    FillRect(game->window, 0, 0, game->window->width, game->window->height, 0, 0, 0);

    FillRect(game->window, game->x1 - game->p_width / 2, game->y1 - game->p_height / 2, game->p_width, game->p_height, 255, 255, 255);
    FillRect(game->window, game->x2 - game->p_width / 2, game->y2 - game->p_height / 2, game->p_width, game->p_height, 255, 255, 255);

    FillRect(game->window, game->ballX - game->ballSize / 2, game->ballY - game->ballSize / 2, game->ballSize, game->ballSize, 0, 255, 255);
}

void UpdateGame(Game* game, InputManager* inputManager)
{
    // Update paddle positions
    game->y1 = game->ballY;
    //game->y2 = inputManager->mouseY;

    int decision = MakeDecision(game);

    if (decision > 0)
    {
        game->y2 += AI_SPEED;
    }
    else
    {
        game->y2 -= AI_SPEED;
    }

    game->v1 = game->y1 - game->y1Prev;
    game->v2 = game->y2 - game->y2Prev;

    game->y1Prev = game->y1;
    game->y2Prev = game->y2;

    if (game->y1 < game->p_height / 2)
    {
        game->y1 = game->p_height / 2;
    }
    else if (game->y1 + game->p_height / 2 >= game->window->height)
    {
        game->y1 = game->window->height - game->p_height / 2;
    }

    if (game->y2 < game->p_height / 2)
    {
        game->y2 = game->p_height / 2;
    }
    else if (game->y2 + game->p_height / 2 >= game->window->height)
    {
        game->y2 = game->window->height - game->p_height / 2;
    }

    // Update ball positions

    int tx = game->ballX + game->ballVx;
    int ty = game->ballY + game->ballVy;

    if (ty - game->ballSize / 2 < 0)
    {
        ty = game->ballSize / 2;
        game->ballVy = -game->ballVy;
    }
    else if (ty + game->ballSize / 2 >= game->window->height)
    {
        ty = game->window->height - game->ballSize / 2;
        game->ballVy = -game->ballVy;
    }

    if (tx - game->ballSize / 2 < 0)
    {
        tx = game->ballSize / 2;
        game->ballVx = -game->ballVx;
    }
    else if (tx + game->ballSize / 2 >= game->window->width)
    {
        tx = game->window->width - game->ballSize / 2;
        game->ballVx = -game->ballVx;
    }

    if (!(game->ballY + game->ballSize / 2 < game->y1 - game->p_height / 2 || game->ballY - game->ballSize / 2 > game->y1 + game->p_height / 2))
    {
        if (tx - game->ballSize / 2 < game->x1 + game->p_width / 2 && tx - game->ballSize / 2 > game->x1 - game->p_width / 2)
        {
            tx = game->x1 + game->p_width / 2 + game->ballSize / 2;
            game->ballVx = -game->ballVx;
        }
        else if (tx + game->ballSize / 2 > game->x1 - game->p_width / 2 && tx + game->ballSize / 2 < game->x1 + game->p_width / 2)
        {
            tx = game->x1 - game->p_width / 2 - game->ballSize / 2;
            game->ballVx = -game->ballVx;
        }
    }

    if (!(game->ballY + game->ballSize / 2 < game->y2 - game->p_height / 2 || game->ballY - game->ballSize / 2 > game->y2 + game->p_height / 2))
    {
        if (tx + game->ballSize / 2 > game->x2 - game->p_width / 2 && tx + game->ballSize / 2 < game->x2 + game->p_width / 2)
        {
            tx = game->x2 - game->p_width / 2 - game->ballSize / 2;
            game->ballVx = -game->ballVx;
        }
        else if (tx - game->ballSize / 2 < game->x2 + game->p_width / 2 && tx - game->ballSize / 2 > game->x2 - game->p_width / 2)
        {
            tx = game->x2 + game->p_width / 2 + game->ballSize / 2;
            game->ballVx = -game->ballVx;
        }
    }

    game->ballX = tx;
    game->ballY = ty;
}

int MakeDecision(Game* game)
{
    // ballx, bally, ballvx, ballvy, y1, y2, v1, v2
    float dataVec[] = {(float) game->ballX / (float) game->window->width, 
                       (float) game->ballY / (float) game->window->height, 
                       (float) game->ballVx / (float) game->window->width, 
                       (float) game->ballVy / (float) game->window->height, 
                       (float) game->y1 / (float) game->window->height, 
                       (float) game->y2 / (float) game->window->height, 
                       game->v1 / (float) game->window->height, 
                       game->v2 / (float) game->window->height};

    float z = 0;

    for (int i = 0; i < 8; i++)
    {
        z += game->ai.weights[i] * dataVec[i];
    }

    z += game->ai.bias;

    z = sigmoid(z);
    
    float zRet = z;

    float zIdeal = game->ballY - game->y2 > 0 ? 1.0f : 0.0f;

    float error = zIdeal - z;
    error *= error;
    //printf("%f\n", error);

    float learnrate = 1;

    float dedz = 2 * (z - zIdeal);

    for (int i = 0; i < 8; i++)
    {
        float dzdw = dataVec[i];
        float dedw = dedz * dzdw;

        game->ai.weights[i] -= learnrate * dedw;
    }

    //dedb = dedz * 1;
    game->ai.bias -= learnrate * dedz;

    if (zRet > 0.5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
