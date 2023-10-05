#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/*lines - строки матрицы, columns - столбцы матрицы
 * arrEl - массив элементов матрицы
 * eps - точность вычислений
*/

int gaussMeth(int lines, int columns, double* arrEl, double eps);//приводит матрицу к ступенчатому ввиду

int main() {
    int lines, columns, i, j , rank;

    double* arrayElement;
    double eps, determinant;

    printf("input matrix size m x n:\n");
    scanf("%d %d", &lines, &columns);

    arrayElement = new double[lines * columns];
    printf("input Elements matrix:\n");

    for (i = 0; i < lines; ++i) {
        for ( j = 0; j < columns; ++j) {
            //Вводим элемент с индексами i, j
            scanf("%lf", &(arrayElement[i * columns + j]));
        }
    }

    printf("input eps:\n");
    scanf("%lf", &eps);

    //Вызываем метод Гаусса

    rank = gaussMeth(lines, columns, arrayElement, eps);//приводит матрицу к ступенчатому ввиду

    //Выводим ступенчатую матрицу
    printf("step matrix:\n");
    for (i = 0; i < lines; ++i) {
        for (j = 0; j < columns; ++j) {
            printf("%10.3lf", arrayElement[i * columns + j]);
        }
        printf("\n");
    }

    printf("rank matrix: %d\n", rank);

    //для квадратичной матрицы можно вычислить ее определитель
    if (lines == columns) {
        determinant = 1.0;
        for (i = 0; i < lines; ++i) {
            determinant *= arrayElement[i * columns + i];
        }
        printf("Determinant matrix: %.3lf\n", determinant);
    }
    delete[] arrayElement;
    getchar();
    return 0;
}

int gaussMeth(int lines, int columns, double* arrEl, double eps) {
    int i, j, k, l;
    double r;
    i = 0; j = 0;

    while(i < lines && j < columns) {
        /*Инвариант: минор матрицы в столбцах 0..j-1
         * уже приведен к ступенчатому виду, и
         * его ранг равен i*/

        /*Ищем максимальный по модулю элемент начиная c i-й строки*/
        r = 0.0;
        for (k = i; k < lines; ++k) {
            if (fabs(arrEl[k * columns + j]) > r) {
                l = k; //запоминаем номер строки
                r = fabs(arrEl[k * columns + j]);// макс элемент
            }
        }
        //если r < eps то столбец является нулевым  (мы обнуляем все элементы столбца на всякий случай т.к
        // там могут быть очень маленькие значения)
        if (r <= eps) {
            for (k = i; k < lines; ++k) {
                arrEl[k * columns + j] = 0.0;
            }
            ++j;// увеличиваем индекс столбца
            continue;//переход к следующей итеррации
        }
        if (l != i) {
            //меняем местами i-ю и l-ю строки
            for (k = j; k < columns; ++k) {
                r = arrEl[i * columns + k];
                arrEl[i * columns + k] = arrEl[l * columns + k];
                arrEl[l * columns + k] = (-r); //меняем знак строки
            }
        }
        // fabs(arrEl[i*columns + j]) > eps

        r = arrEl[i * columns + j];
        assert(fabs(r) > eps);

        //Обнуляем j-й столбец, начиная со строки i + 1,
        //применяя элементарные преобразования 2-го рода
        for (k = i + 1; k < lines; ++k) {
            double c = ((-arrEl[k * columns + j]) / r);

            // К к-й строке прибавляем i-ю
            // умноженную на С
            arrEl[k * columns + j] = 0.0;
            for (l = j + 1; l < columns; ++l) {
                arrEl[k * columns + l] += c * arrEl[i * columns + l];
            }
        }
        ++i; ++j;
    }
    return i; //возвращаем число не нулевых строк
}
