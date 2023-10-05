#include <iostream>
using namespace std;

// dy^2/d^2x = f(x,y,v)
//double f(double x, double y, double v) {
//	return v-y/x;
//    //return (y+v+x*x)/x;
//}

double rungeKutta2time(double x, double& y, double& v, double h) {
//	double t1 = v + h/2*v;
//	double t2 = v + h*t1;
//	double k1 = y +h/2*f(x,y,v);
//	double k2 = y + h*f(x+h/2,t2,v);
//	y=k2;
//	v=t2;
    double k1 = h * v;
    double l1 = h * f(x, y, v);
    double k2 = h * (v + 0.5 * l1);
    double l2 = h * f(x + 0.5 * h, y + 0.5 * k1, v + 0.5 * l1);
    y += k2;
    v += l2;
}

//int main() {
//	setlocale(LC_ALL, "Russian");
//
//    double x0;        // Initial x
//    double y0;        // Initial y
//    double v;
//    double h;         // Step size
//    int numSteps;
//    
//    cout << "Введите x0: ";
//    cin >> x0;
//    cout << "Введите y0: ";
//    cin >> y0;
//    cout << "Введите y`: ";
//    cin >> v;
//    cout << "Введите количество шагов: ";
//    cin >> numSteps;
//    cout << "Введите размер шага h: ";
//    cin >> h;
//
//    cout << "Начальные условия: y(" << x0 << ") = " << y0 << endl;
//    for (int i = 0; i < numSteps; ++i) {
//        rungeKutta2time(x0, y0, v, h);
//        x0 += h;
//        cout << "Шаг " << i + 1 << ": y(" << x0 << ") = " << y0 << ", y'(" << x0 << ") = " << v << endl;
//    }
//	
//	system("pause");
//    return 0;
//}

