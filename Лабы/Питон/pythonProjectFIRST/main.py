import sympy as sp
import numpy as np
import decimal
from decimal import Decimal as Dec

decimal.getcontext().prec = 30


def method_gauss(a):
    # Прямой ход
    for c in range(len(a[0]) - 2):  # Цикл по столбцам
        for i in range(c + 1, len(a)):  # Цикл по строкам
            coef = a[i][c] / a[c][c] * -1
            for j in range(c, len(a[i])):  # Цикл по ячейкам
                a[i][j] += a[c][j] * coef

    # Обратный ход
    for c in range(len(a) - 1, -1, -1):
        for i in range(len(a) - 1, c, -1):
            a[c][-1] -= a[c][i]
        a[c][-1] /= a[c][c]
        for i in range(0, len(a)):
            a[i][c] *= a[c][-1]

    return list([i[-1]] for i in a)


def matrix_print(matrix):
    for row in matrix:
        for x in row:
            print("{:45}".format(x), end="")
        print()


def matrix_multiplication(a: list, b: list):
    res = []
    if len(a[0]) != len(b):
        print("Матрицы не могут быть перемножены")
        exit()
    else:
        temp = 0
        row = []
        for z in range(len(a)):  # строки a
            for j in range(len(b[0])):  # столбцы b
                for i in range(len(b)):  # строки b && столбцы a
                    temp += a[z][i] * b[i][j]
                row.append(temp)
                temp = 0
            res.append(row)
            row = []
    return res


def matrix_subtraction(a: list, b: list):
    res = []
    if len(a[0]) != len(b[0]) or len(a) != len(b):
        print("Матрицы не могут быть вычтены")
        exit()
    else:
        for i in range(len(a)):
            row = []
            for j in range(len(a[0])):
                row.append(a[i][j] - b[i][j])
            res.append(row)

    return res


def det(mat: list):
    s = len(mat)
    k = Dec(1)
    d = Dec(0)

    if s == 1:
        d = mat[0][0]
    elif s == 2:
        d = mat[0][0] * mat[1][1] - (mat[1][0] * mat[0][1])
    elif s > 2:
        for i in range(s):
            d = d + k * mat[i][0] * det([mat[j][1:] for j in range(s) if j != i])
            k = -k
    return d


def transpose(mat: list):
    res = []
    n = len(mat)
    m = len(mat[0])
    for j in range(m):
        tmp = []
        for i in range(n):
            tmp.append(mat[i][j])
        res.append(tuple(tmp))
    return tuple(res)


def main():
    """ Входные данные """
    # """
    x, y = sp.symbols('x, y')
    symbs = [x, y]
    funcs = ((x ** 2) + (y ** 2) - 4, (x / y ** 2) - 2)
    roots0 = [[Dec('2.0')], [Dec('1.0')]]
    epsilon = 1e-6
    # """
    """
    x, y = sp.symbols('x, y')
    symbs = [x, y]
    funcs = (x * y - 2.3, x / y - 1.9)
    roots0 = [[Dec('2.0')], [Dec('1.0')]]
    epsilon = 1e-8
    """
    """
    x, y, z = sp.symbols('x, y, z')
    symbs = [x, y, z]
    funcs = (x ** 2 + y ** 2 + z ** 2 - 1,
             2 * x ** 2 + y ** 2 - 4 * z,
             3 * x ** 2 - 4 * y + z ** 2)
    roots0 = [[Dec('0.5')], [Dec('0.5')], [Dec('0.5')]]
    epsilon = 1e-16
    """
    print(end='')
    print("Система уравнений: ", ("\n\t* '{}'" * len(funcs)).format(*funcs))
    print()
    print("x(нач.): ", *(i[0] for i in roots0))
    diff_funcs = tuple(tuple(sp.diff(fun, i) for i in symbs) for fun in funcs)
    if len(diff_funcs) != len(diff_funcs[0]):
        raise Exception('Invalid matrix. The matrix must be square.')

    print()
    print("dF/dx:")
    for i in diff_funcs:
        print('\t', i)

    transpon = transpose(list(diff_funcs))  # Транспонированная матрица
    print("\n(dF/dx)^T:")
    for i in transpon:
        print('\t', i)

    determinant = det(list(diff_funcs))  # определитель
    if determinant == 0:
        raise Exception('The determinant is zero.')
    print("\n△ = ", determinant)

    obrat = []  # Обратная матрица, без определителя
    for i in range(len(transpon)):
        tmp = []
        for j in range(len(transpon[0])):
            tmp.append((-1) ** (i + j + 2) * det(
                [[transpon[k][kk] for kk in range(len(transpon[0])) if kk != j] for k in range(len(transpon)) if
                 k != i]))
        obrat.append(tuple(tmp))
    obrat = tuple(obrat)
    # print(f"(dF/dx)^-1 = {1/determinant} *", obrat)

    print('~' * 120)

    """ Многомерный метод Ньютона с помощью алгебраических дополнений """
    roots_p = roots = roots0
    check = True
    count = 1
    print('"'*69 + '\n""" Многомерный метод Ньютона с помощью алгебраических дополнений """\n' + '"'*69)
    while check:
        print('~' * 10 + ' ' * 5 + "ШАГ #" + str(count) + ' ' * 5 + '~' * 10)
        print()

        print("X prev: ")
        matrix_print(roots)

        """ Вывод F(x)(с подставленными x) """
        funcs_x = []
        for i in range(len(funcs)):
            funcs_x.append([Dec(str(funcs[i].subs([(symbs[k], roots[k][0]) for k in range(len(roots))])))])
        print("F(x): ")
        matrix_print(funcs_x)

        """ Вывод dF/dx(с подставленными x) """
        diff_funcs_x = []
        for i in range(len(diff_funcs)):
            tmp = []
            for j in range(len(diff_funcs[0])):
                tmp.append(Dec(str(diff_funcs[i][j].subs([(symbs[k], roots[k][0]) for k in range(len(roots))]))))
            diff_funcs_x.append(tmp)
        print("dF/dx: ")
        matrix_print(diff_funcs_x)

        """ Вывод (dF/dx)^T (с подставленными x) """
        transpon_x = transpose(diff_funcs_x)
        print("(dF/dx)^T: ")
        matrix_print(transpon_x)

        """ Вывод △(с подставленными x) """
        determinant_x = det(diff_funcs_x)
        if determinant_x == 0:
            raise Exception('The determinant is zero.')
        print("\n△ = : " + str(determinant_x) + '\n')

        """ Вывод (dF/dx)^-1 (с подставленными x) """
        obrat_x = []
        for i in range(len(diff_funcs)):
            tmp = []
            for j in range(len(diff_funcs[0])):
                tmp.append(Dec(
                    str((1 / determinant_x) * obrat[i][j].subs([(symbs[k], roots[k][0]) for k in range(len(roots))]))))
            obrat_x.append(tmp)
        print("(dF/dx)^-1 = △ * (мат. алгеб. доп.((dF/dx)^-1)) : ")
        matrix_print(obrat_x)

        roots = matrix_subtraction(roots, matrix_multiplication(obrat_x, funcs_x))
        print("X: ")
        matrix_print(roots)

        check = (max(sum(abs(j) for j in i) for i in matrix_subtraction(roots, roots_p)) > epsilon)

        if check:
            roots_p = roots
            count += 1
            print("\n\n")

    print("\n\n")

if __name__ == "__main__":
    main()