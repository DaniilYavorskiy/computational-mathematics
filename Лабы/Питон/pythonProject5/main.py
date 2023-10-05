import graphics as gr
import math
import numpy as np

window = gr.GraphWin("", 600, 600)

x = [1.000, 2.0000, 4.0000, 6.0000]
y = [2.000, 5.0000, 6.00000, 7.0000]

C = [0.0000, 0.0000, 0.0000, 0], [0.0000, 0.0000, 0.0000, 0], [0.000, 0.000, 0.000, 0], [0.000, 0.000, 0.000, 0]

Y = [0.000, 0.000, 0.000, 0.000]

O = []

lines = []


def g1(x):
    return 1


def g0(x):
    return x


def g2(x):
    return x ** 2


def g3(x):
    return x ** 3


def fill_C(C, x):
    g = [g0, g1, g2, g3]
    n = len(g)
    for i in range(n):
        for j in range(n):
            for k in range(len(x)):
                C[i][j] += g[i](x[k]) * g[j](x[k])


def fill_Y(Y, y, x):
    for i in range(0, len(Y)):
        count = 0
        if (i == 0):
            for j in range(0, len(y)):
                count = count + y[j] * g0(x[j])
        if (i == 1):
            for j in range(0, len(y)):
                count = count + y[j] * g1(x[j])
        if (i == 2):
            for j in range(0, len(y)):
                count = count + y[j] * g2(x[j])
        if (i == 3):
            for j in range(0, len(y)):
                count = count + y[j] * g3(x[j])
        Y[i] = count


fill_C(C, x)
fill_Y(Y, y, x)
O = np.linalg.solve(C, Y)

x_graf = []
y_graf = []
y_graf1 = []

point = 1000
temp = 0.700


def func(x, O):
    count = O[0] * x + O[1] + O[2] * math.sqrt(x) + O[3] * (math.e ** x)
    return count


for i in range(0, point):
    x_graf.append(temp)
    temp += 0.006
for i in range(0, len(x_graf)):
    y_graf.append(func(x_graf[i], O))


def dots():
    for i in range(0, len(x)):
        t = gr.Circle(gr.Point((100 + x[i] * 50), (500 - y[i] * 50)), 2)
        t.setFill("yellow")
        lines.append(t)


lines.append(gr.Line(gr.Point(100, 0), gr.Point(100, 600)))
lines.append(gr.Line(gr.Point(0, 500), gr.Point(600, 500)))

for i in range(0, 10):
    lines.append(gr.Line(gr.Point(80, 50 * i), gr.Point(120, 50 * i)))
    lines.append(gr.Line(gr.Point(100 + 50 * i, 480), gr.Point(100 + 50 * i, 520)))
    lines.append(gr.Text(gr.Point(60, 50 + 50 * i), (9 - i)))
    lines.append(gr.Text(gr.Point(100 + 50 * i, 540), (i)))

k = 1 / 50
q = -1
for i in range(0, point - 1):
    q = q + 1
    t = gr.Line(gr.Point((100 + x_graf[q] * 50), 500 - y_graf[q] / k),
                gr.Point(((100 + x_graf[q + 1] * 50)), 500 - y_graf[q + 1] / k))
    t.setOutline('red')
    lines.append(t)
print(x_graf, "\n", y_graf)
dots()

for q in lines:
    q.draw(window)

window.getMouse()
window.close()


