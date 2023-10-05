import graphics as gr
import math as m  
import numpy as np
window = gr.GraphWin("Spline", 600, 600)

h = 0.5
H = 1/h
N = 3

M = 0
0.2
def dots(n):
    for i in range(0, n+1):
        t = gr.Circle(gr.Point(100+(M*100)+(40*i*2.5/H), 500-(yq[i]*100)), 2)
        t.setFill("yellow")
        lines.append(t)


xq = []
yq = []
def y(x):
    return m.sqrt(x)*2

for i in range(0, 100):
    xq.append(M+i/H) 
    yq.append(y(M+i/H))


x_arr = xq[:N+1]
y_arr = yq[:N+1]

def p(x, n):
    n = len(x_arr)
    h = np.diff(x_arr)
    d = np.diff(y_arr) / h
    C = np.zeros((n, n))
    C[0, 0] = 1
    C[-1, -1] = 1

    for i in range(1, n-1):
        C[i, i-1] = h[i-1] / 6
        C[i, i] = (h[i-1] + h[i]) / 3
        C[i, i+1] = h[i] / 6

    D = np.zeros((n, 1))
    D[1:-1, 0] = d[1:] - d[:-1]

    M = np.linalg.solve(C, D)

    i = np.searchsorted(x_arr, x) - 1

    h_i = x_arr[i+1] - x_arr[i]

    term1 = (M[i] * (x_arr[i+1] - x)**3) / (6 * h_i)
    term2 = (M[i+1] * (x - x_arr[i])**3) / (6 * h_i)
    term3 = ((y_arr[i] - (M[i] * h_i**2) / 6) * (x_arr[i+1] - x) / h_i)
    term4 = ((y_arr[i+1] - (M[i+1] * h_i**2) / 6) * (x - x_arr[i]) / h_i)

    return term1+term2+term3+term4

lines = []


lines.append(gr.Line(gr.Point(100, 0), gr.Point(100, 600)))
lines.append(gr.Line(gr.Point(0, 500), gr.Point(600, 500)))


for i in range(0, 20):
    lines.append(gr.Line(gr.Point(80, 25*i), gr.Point(120, 25*i)))
    lines.append(gr.Line(gr.Point(100+25*i, 480), gr.Point(100+25*i, 520)))
    lines.append(gr.Text(gr.Point(60, 25+25*i), (19-i)/4)) 
    if(i%2==0):
        lines.append(gr.Text(gr.Point(100+25*i, 540), (i)/4)) 
    else:
        lines.append(gr.Text(gr.Point(100+25*i, 560), (i)/4)) 

dots(N)

for i in range(0, int(600)):
    w = gr.Line(gr.Point(100+(i), 500-y(i/100)*100), gr.Point(100+((i+1)), 500-y((i+1)/100)*100))
    w.setOutline('red')
    lines.append(w)
    if(i/100<x_arr[N] and i/100>x_arr[0]):

        t = gr.Line(gr.Point(100+(i), 500-p(i/100, N)*100), gr.Point(100+((i+1)), 500-p((i+1)/100, N)*100))
        t.setOutline('blue')
        lines.append(t)




for q in lines:
    q.draw(window)


window.getMouse()
window.close()