import math
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

solution = pd.read_csv (r'/home/kyleperez/cppstuff/secsolution.csv', header=0)

x = solution['x']
yone = solution['f(x)one']
dyone = solution['df(x)one']
ytwo = solution['f(x)two']
dytwo = solution['df(x)two']
ythree = solution['f(x)three']
dythree = solution['df(x)three']

plt.plot(x, yone, 'r', label='1st order')
#plt.plot(x, ytwo, 'b', label='2nd order')
#plt.plot(x, ythree, 'g', label='3rd order')
plt.plot(x, (1.0/6.0)*x**3, 'k', label='Analytic')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Solution to df/dx = x | f(0) = 0')
plt.legend()
plt.show()
