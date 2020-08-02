#coding=utf-8
import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#######################################################
sampleNum = 200
x = np.linspace(0., 2. * math.pi, sampleNum)
y = np.zeros(sampleNum)

for i in range(0, sampleNum):
    y[i] = math.cos(x[i])

#######################################################
fig1, ax1 = plt.subplots(1, 1)