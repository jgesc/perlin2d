#include "perlin2d.h"
#include <stdio.h>

const float SQRT2 = sqrt(2);

int perlin2d(float * grid, size_t height, size_t width, unsigned int t, float a, unsigned int seed)
{
  int i, j; // Iterator variables

  // Initialize PRNG
  srand(seed);

  // Allocate space for random vector grid
  size_t vgridxl = width % t ? width / t + 2 : width / t + 1;
  size_t vgridyl = height % t ? height / t + 2 : height / t + 1;
  float * vgrid = malloc(vgridxl * vgridyl * 2 * sizeof(float));
  if(!vgrid) return 0;
  // Fill random vector grid
  for(i = 0; i < vgridxl * vgridyl * 2; i += 2)
  {
    // Generate random unitary 2D vector
    float x = ((float)rand() / RAND_MAX) * 2 - 1;
    float y = ((float)rand() / RAND_MAX) * 2 - 1;
    float xn = NORM(x, y);
    float yn = NORM(y, x);

    // Store vector
    vgrid[i] = xn;
    vgrid[i + 1] = yn;
  }

  // Interpolate values
  for(i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {
      // Get top-left random vector index
      int x = j / t;
      int y = i / t;
      // Get relative position in cell
      float u = j % t + 1;
      float v = i % t + 1;

      // Calculate corner-point vectors (clockwise order)
      float d = SQRT2; // Normalize
      float vec1[2] = {u / t / d, v / t / d};
      float vec2[2] = {-(t - u) / t / d, v / t / d};
      float vec3[2] = {-(t - u) / t / d, -(t - v) / t / d};
      float vec4[2] = {u / t / d, -(t - v) / t / d};

      // Calculate dot products
      float dots[4] =
      {
        DOT(vec1, vgrid + ((y * vgridxl + x) * 2)),
        DOT(vec2, vgrid + ((y * vgridxl + (x + 1)) * 2)),
        DOT(vec3, vgrid + (((y + 1) * vgridxl + (x + 1)) * 2)),
        DOT(vec4, vgrid + (((y + 1) * vgridxl + x) * 2))
      };

      // Interpolate
      float avgt = LERP(dots[0], dots[1], SMOOTH((u - 1) / (t - 1)));
      float avgb = LERP(dots[3], dots[2], SMOOTH((u - 1) / (t - 1)));
      float val = LERP(avgt, avgb, SMOOTH((v - 1) / (t - 1)));

      // Store result
      grid[i * width + j] = (val + 0.5) * a;
    }
  }

  // Free vector grid
  free(vgrid);

  return 1;
}
