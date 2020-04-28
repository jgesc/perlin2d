#include <stdio.h>
#include "../src/perlin2d.h"

int main(void)
{
  float * noise1 = malloc(4096 * 4096 * sizeof(float));
  float * noise2 = malloc(4096 * 4096 * sizeof(float));
  float * noise3 = malloc(4096 * 4096 * sizeof(float));
  float * noise4 = malloc(4096 * 4096 * sizeof(float));
  float * noise5 = malloc(4096 * 4096 * sizeof(float));


  perlin2d(noise1, 4096, 4096, 1024, 0.5, 32454);
  perlin2d(noise2, 4096, 4096, 512, 0.25, 986);
  perlin2d(noise3, 4096, 4096, 256, 0.125, 412345123);
  perlin2d(noise4, 4096, 4096, 128, 0.075, 454);
  perlin2d(noise5, 4096, 4096, 64, 0.035, 3477754);

  int i;
  FILE * f = fopen("octaves.txt", "w");
  for(i = 0; i < 4096 * 4096; i++)
    fprintf(f, "%f\n", noise1[i] + noise2[i] + noise3[i] + noise4[i] + noise5[i]);
  fclose(f);

  free(noise1);
  free(noise2);
  free(noise3);
  free(noise4);
  free(noise5);


  return 0;
}
