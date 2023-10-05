import numpy as np
from scipy import interpolate
import math

# Define the original function f(x)
def f(x):
    return x * x

# Generate some sample data points
x = np.linspace(0, 2*np.pi, 4)  # sample x-values
y = f(x) + np.random.normal(0, 0.1, len(x))  # corresponding y-values with some error

# Choose a class of functions G (e.g., polynomials)
G = np.poly1d  # class of polynomials

# Perform approximation using interpolation
g = interpolate.interp1d(x, y, kind='linear')  # interpolate using linear interpolation

# Evaluate the interpolated function at some new points
x_new = np.linspace(0, 2*np.pi, 100)
y_approx = g(x_new)

# Plot the original function and the approximation
import matplotlib.pyplot as plt

plt.plot(x, y, 'go', label='')
plt.plot(x_new, f(x_new), 'r-', label='График функции')
plt.plot(x_new, y_approx, 'b-', label='Аппроксимация')
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Function Approximation')
plt.show()
