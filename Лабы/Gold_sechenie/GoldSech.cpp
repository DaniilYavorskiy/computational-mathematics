#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x) {
       return  x*x-6*x; //y=x^2-6x
}

int main() {
    int i, flag = 1;
    double a, b, x1, x2, y1, y2, eps = 0.000000001, fi = 1.618, x;
    a = 0;
    b = 10;
    x1 = b - ((b - a) / fi);
    x2 = a + ((b - a) / fi);
    y1 = f(x1);
    y2 = f(x2);

    printf("Metod zolotogo secheniya :\n");
    printf("[%lf;%lf]\n", a, b);

    for (i = 1; flag == 1; i++) {
        if (y1 < y2) { // если  > то будет max
            b = x2;
            x2 = x1;
            x1 = b - ((b - a) / fi);
            y2 = y1;
            y1 = f(x1);
        }
        else {
            a = x1;
            x1 = x2;
            x2 = a + ((b - a) / fi);
            y1 = y2;
            y2 = f(x2);
        }
        printf("shag  %d , interval: [%lf;%lf]\n", i, a, b);
        if ((b - a) < eps) {
            flag = 0;
            x = (a + b)/2;
        }
    }
    printf("x = %lf, f(%lf) = %lf\n", x, x, f(x));
    return 0;
}

