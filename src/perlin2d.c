#include "perlin2d.h"

int perlin2d(float * grid, size_t height, size_t width, unsigned int t, float a, unsigned int seed)
{
  int i, j; // Iterator variables

  // Initialize PRNG
  srand(seed);

  // Allocate space for random vector grid
  size_t vgridxl = width % t ? width / t + 1 : width / t;
  size_t vgridyl = height % t ? height / t + 1 : height / t;
  float * vgrid = malloc(vgridxl * vgridyl * 2 * sizeof(float));
  if(!vgrid) return 0;
  // Fill random vector grid
  for(i = 0; i < vgridxl * vgridyl * 2; i += 2)
  {
    // Generate random unitary 2D vector
    float x = rand() / RAND_MAX;
    float y = rand() / RAND_MAX;
    float xn = NORM(x, y);
    float yn = NORM(y, x);

    // Store vector
    vgrid[i] = xn;
    vgrid[i + 1] = yn;
  }

  // Interpolate values
  for(i = 0; i < width; i++)
  {
    for(j = 0; j < height; j++)
    {
      // Get top-left random vector index
      int x = i / t;
      int y = i % t;
      // Get relative position in cell
      float u = i % t;
      float v = j % t;

      // Calculate corner-point vectors (clockwise order)
      float vec1[2] = {NORM(u, v), NORM(v, u)};
      float vec2[2] = {NORM(t - u, v), NORM(v, t - u)};
      float vec3[2] = {NORM(t - u, t - v), NORM(t - v, t - u)};
      float vec4[2] = {NORM(y, t - v), NORM(t - v, y)};

      // Calculate dot products
      float dots[4] =
      {
        DOT(vec1, vgrid + (y * vgridxl + x * 2)),
        DOT(vec2, vgrid + (y * vgridxl + (x + 1) * 2)),
        DOT(vec3, vgrid + ((y + 1) * vgridxl + (x + 1) * 2)),
        DOT(vec4, vgrid + ((y + 1) * vgridxl + x * 2))
      };

      // Interpolate
      float a = LERP(dots[0], dots[1], u / t);
      float b = LERP(dots[4], dots[3], u / t);
      float val = LERP(a, b, v / t);

      // Store result
      grid[i * width + j] = val;
    }
  }

  // Free vector grid
  free(vgrid);

  return 1;
}
