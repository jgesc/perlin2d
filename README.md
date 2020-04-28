# Introduction
Perlin noise 2D implementation written in C.

# Documentation
```C
int perlin2d(float * grid, size_t height, size_t width, unsigned int t, float a, unsigned int seed);
```
## Arguments
* **grid**: pointer to the memory block were the result will be stored. Must be of size `height * width * sizeof(float)`.
* **height**: height of the image to generate.
* **width**: width of the image to generate.
* **t**: period of random vector generation. Noise frequency = 1/t.
* **a**: amplitude of the noise.
* **seed**: seed used for RNG.

## Returns
* `1` if everything worked.
* `0` if could not allocate memory for random vectors

# Benchmark
Generated the following image with size 4096x4096 and T = 64 in 0.23 seconds on a i7-4770k.

![Noise example](/res/Figure_1.png)

# Example
The code in the folder `example` generates five noise images, adds them to generate fractal noise and writes the result as a txt file.
There is a Python script included to visualize de result.

![Fractal noise](/res/Figure_2.png)

To use the example, cd into the example folder and run:
```Bash
make
./test
python3 view.py
```

For the Python visualization script to work, requires Numpy and Matplotlib.
