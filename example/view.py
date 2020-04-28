import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("octaves.txt").reshape((4096, 4096))
plt.imshow(data, cmap='gray')
plt.show()