#include <iostream>
#include <cmath>
using namespace std;

// dy^2/d^2x = f(x,y,v)
double f(double x, double y, double v) {
    return (exp(x-1)+y+v)/3;;
    //return (y+v+x*x)/x;
}

double euler(double x, double& y, double& v, double h) {
    double t1 = y + h*v;
    double t2 = v + h*(f(x,y,v));
    y=t1;
    v=t2;
}

//int main() {
//	setlocale(LC_ALL, "Russian");
//    
//    double x;        // Initial x
//    double y;        // Initial y
//    double v;		
//    double h;        // Step size
//    double numSteps;       
//    
//    cout << "Введите x0: ";
//    cin >> x;
//    cout << "Введите y0: ";
//    cin >> y;
//    cout << "Введите y`: ";
//    cin >> v;
//    cout << "Введите количество шагов: ";
//    cin >> numSteps;
//    cout << "Введите размер шага h: ";
//    cin >> h;
//    
//    cout << "Начальные условия: y(" << x << ") = " << y << endl;
//    for (int i = 0; i < numSteps; ++i) {
//        euler(x, y, v, h);
//        x += h;
//        cout << "Шаг " << i + 1 << ": y(" << x << ") = " << y << ", y'(" << x << ") = " << v << endl;
//    }
//    system("pause");
//    return 0;
//}
