#ifndef __PERLIN2D_H__
#define __PERLIN2D_H__

#include <stdlib.h>

#define NORM(X,Y) (X + Y) ? X / (X + Y) : 0
#define DOT(A,B) (A)[0] * (B)[0] + (A)[1] * (B)[1]
#define LERP(A,B,T) (A * T + B * (1 - T))

int perlin(float * grid, size_t height, size_t width, unsigned int t, float a, unsigned int seed);

#endif
