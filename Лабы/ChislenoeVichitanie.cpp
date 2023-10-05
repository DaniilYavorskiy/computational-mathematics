//программа для численного вычитания двух чисел с плавающей точкой:

#include <iostream>
#include <cmath>

using namespace std;

// Функция для численного вычитания a - b
double numericalSubtraction(double a, double b) {
    double precision = 1E-9; // задаем точность вычислений
    double result = a;
    int iterations = 0;
    while (abs(result - b) > precision) { // выполняем итерации до достижения необходимой точности
        result -= b;
        iterations++;
    }
    cout << "Число итераций: " << iterations << endl;
    return result;
}

// пример использования
int main() {
    double a = 10.5;
    double b = 2.3;
    double subtraction = numericalSubtraction(a, b);
    cout << "Вычитание " << b << " из " << a << " равно " << subtraction << endl;
    return 0;
}

//В этой программе numericalSubtraction - это функция, которая принимает два числа с плавающей точкой a и b и вычисляет их разность методом численного вычитания. Функция использует заданную точность precision для определения, когда необходимо закончить итерации. Функция возвращает разность a - b.