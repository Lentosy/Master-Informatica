import numpy as np
from numpy.random import random_sample
from numpy import sin, cos, pi
from numpy.fft import fft, fftshift

import matplotlib.pyplot as plt

samplingFrequency = 100
samplingInterval = 1 / samplingFrequency

beginTime = 0
endTime = 10

frequency = 7

time = np.arange(beginTime, endTime, samplingInterval)

wave = sin(2*pi*samplingFrequency*time)

fourierTransform = fft(wave)/len(wave)
fourierTransform = fourierTransform[range(int(len(wave)/2))]

plt.plot(time[0:500], fourierTransform)
plt.show()
