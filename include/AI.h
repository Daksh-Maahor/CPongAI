#ifndef AI_H_
#define AI_H_

#include <math.h>

#define AI_SPEED 5.0f

inline float sigmoid(float x)
{
    return 1 / (1 + expf(-x));
}

inline float sigmoidDeriv(float y)
{
    return y * (1 - y);
}

typedef struct
{
    float weights[8];
    float bias;
} AI;

void InitialiseAI(AI*);
void PrintAI(AI*);

#endif
