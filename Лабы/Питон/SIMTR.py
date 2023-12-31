from typing import List
import numpy as np
from decimal import Decimal as Dec
import math

def fun(x: Dec) -> Dec:
    return Dec.sqrt(x)


def formulaTrapeze(x_arr: List[Dec], y_arr: List[Dec]) -> Dec:
    res = Dec("0")
    for i in range(len(x_arr) - 1):
        res += ((x_arr[i + 1] - x_arr[i]) * (Dec("0.5") * y_arr[i] + Dec("0.5") * y_arr[i + 1]))
    return res


def formulaSimpson(x_arr: List[Dec], y_arr: List[Dec]) -> Dec:
    res = Dec("0")
    for i in range(0, len(x_arr) - 2, 2):
        res += ((x_arr[i + 2] - x_arr[i]) * (Dec("1")/Dec("6") * y_arr[i] + Dec("2")/Dec("3") * y_arr[i + 1] + Dec("1")/Dec("6") * y_arr[i + 2]))
    return res


def main():
    epsilon = Dec(str(input("Введите необходимую точность(кол-во знаков после запятой):  ")))
    left = Dec(str(input("Нижний предел интегрирования:  ")))
    right = Dec(str(input("Верхний предел интегрирования:  ")))
    h_st = Dec(str(input("Шаг:  ")))

    h = h_st
    print('~' * 10, "Формула Трапеций ", '~' * 10, '\n')
    while True:
        x_arr = [i for i in np.arange(left, right + h, h)]
        y_arr = [fun(i) for i in x_arr]
        first = formulaTrapeze(x_arr, y_arr)
        x_arr = [i for i in np.arange(left, right + h/2, h/2)]
        y_arr = [fun(i) for i in x_arr]
        second = formulaTrapeze(x_arr, y_arr)
        print(first, second, h)
        if abs(first - second) < 3 * epsilon:
            break
        h /= 2


    h = h_st
    print('~' * 10, "Формула Симпсона ", '~' * 10, '\n')

    while True:
        x_arr = [i for i in np.arange(left, right + h, h)]
        y_arr = [fun(i) for i in x_arr]
        first = formulaSimpson(x_arr, y_arr)
        x_arr = [i for i in np.arange(left, right + h/2, h/2)]
        y_arr = [fun(i) for i in x_arr]
        second = formulaSimpson(x_arr, y_arr)
        print(first, second, h)
        if abs(first - second) < 15 * epsilon:
            break
        h /= 2


if __name__ == '__main__':
    main()

