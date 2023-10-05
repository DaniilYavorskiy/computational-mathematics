ZT = 6


def f(x):
    return round(x**2 - 6 * x, ZT)

a = 0
b = 10
x1 = b - ((b - a) / 1.618)
x2 = a + ((b - a) / 1.618)
y1 = f(x1)
y2 = f(x2)
eps = 0.0001
flag = True
i = 1

while flag:
    if y1 < y2:
        b = x2
        x2 = x1
        x1 = round(b - ((b - a) / 1.618), ZT)
        y2 = y1
        y1 = f(x1)
    else:
        a = x1
        x1 = x2
        x2 =  round(a + ((b - a) / 1.618), ZT)
        y1 = y2
        y2 = f(x2)
    print(i, ") ", round(a, ZT), round(b, ZT))
    i += 1
    if (b - a)/2 < eps:
        flag = False
        x = (a + b) / 2

print('\n')
print('x =', x)
print('f(x) =', f(x))