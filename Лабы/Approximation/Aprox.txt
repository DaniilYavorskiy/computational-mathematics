import math
import pylab
import numpy
from franges import frange
import matplotlib.pyplot as plt

pow_polynom = 3
x_0 = 0
n = 4
h = 1
f = lambda x: math.pow(x, 2)

res = []
for i in range(0, pow_polynom):
    res.append(0.)


def g(number, x):
    if number == 0:
        return 1
    if number == 1:
        return x
    if number == 2:
        return math.sqrt(x)


def get_coefficient(array):
    coefficients = []
    for i in range(0, pow_polynom):
        coefficients.append([])
        for j in range(0, pow_polynom):
            coefficients[i].append(0.)
    for i in range(0, pow_polynom):
        for j in range(0, pow_polynom):
            for k in range(0, n):
                coefficients[i][j] += g(i, array[k][0]) * g(j, array[k][0]) * 1.
    tmp = []
    for i in range(0, pow_polynom):
        tmp.append(0.)
    for i in range(0, pow_polynom):
        for j in range(0, n):
            tmp[i] += array[j][1] * g(i, array[j][0]) * 1.
    tmp = list(numpy.linalg.solve(coefficients, tmp))
    tmp.reverse()
    return tmp


def approx_function(coef, x):
    value = 0.
    k = pow_polynom - 1
    for i in range(0, pow_polynom):
        value += coef[i] * g(k, x) * 1.;
        k = k - 1
    return value


array_x_y = []
for i in range(0, n):
    array_x_y.append([])
    for j in range(0, n):
        array_x_y[i].append(0.)

for i in range(0, n):
    array_x_y[i][0] = x_0 + i * h * 1.
    array_x_y[i][1] = f(array_x_y[i][0]) * 1.


zlist = list(frange(0, 3, 0.01))
glist = list(range(x_0, n, h))

res = get_coefficient(array_x_y)

pylab.grid()
pylab.plot(zlist, [f(x) for x in zlist], 'r-', label='График функции')
pylab.plot(zlist, [approx_function(res, x) for x in zlist], 'b-', label='Аппроксимация')
pylab.plot(glist, [approx_function(res, x) for x in glist], "go")
plt.legend()
pylab.show()


def main():
    return


if __name__ == '__main__':
    main()