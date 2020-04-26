#ifndef __PERLIN2D_H__
#define __PERLIN2D_H__

#include <stdlib.h>
#include <math.h>

#define NORM(X,Y) ((sqrt((X)*(X) + (Y)*(Y))) != 0 ? (X) / (sqrt((X)*(X) + (Y)*(Y))) : 0)
#define DOT(A,B) ((A)[0] * (B)[0] + (A)[1] * (B)[1])
#define LERP(A,B,T) (A * (1 - T) + B * T)

int perlin2d(float * grid, size_t height, size_t width, unsigned int t, float a, unsigned int seed);

#endif
