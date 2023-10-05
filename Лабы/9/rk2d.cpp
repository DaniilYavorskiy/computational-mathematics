#include <iostream>
using namespace std;

// dy^2/d^2x = f(x,y,v)
//double f(double x, double y, double v) {
//    return v-y/x;
//    //return (y+v+x*x)/x;
//}

double rungeKutta2diff(double x, double& y, double& v, double h) {
//	double t1 = v + h/2*v;
//	double t2 = v + h*t1;
//	double k1 = y + h*f(x+h/2,t2,v);
//	double k2 = y + h/2*(f(x,y,v)+f(x+h, k1, v));
//	y=k2;
//	v=t2;
	double k1 = h * v;
    double l1 = h * f(x, y, v);
    double k2 = h * (v + l1);
    double l2 = h * f(x + h, y + k1, v + l1);
    y += 0.5 * (k1 + k2);
    v += 0.5 * (l1 + l2);
}

//int main() {
//	setlocale(LC_ALL, "Russian");
//	
//    double x;        // Initial x
//    double y;        // Initial y
//    double v;		// Initial y'
//    
//    double h;         // Step size
//    int numSteps;
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
//        rungeKutta2diff(x, y, v, h);
//        x += h;
//        cout << "Шаг " << i + 1 << ": y(" << x << ") = " << y << ", y'(" << x << ") = " << v << endl;
//    }
//    
//    system("pause");
//    return 0;
//}
