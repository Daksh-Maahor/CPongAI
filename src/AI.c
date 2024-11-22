#include "AI.h"
#include <stdlib.h>
#include <stdio.h>

void InitialiseAI(AI* ai)
{
    ai->bias = 0.0f;
    for (int i = 0; i < 8; i++)
    {
        ai->weights[i] = (float)rand() / (float)(RAND_MAX / 2) - 1;
    }
}

void PrintAI(AI* ai)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%f\n", ai->weights[i]);
    }

    printf("\n");
    
    printf("%f\n", ai->bias);
}
