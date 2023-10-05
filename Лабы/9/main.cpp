#include <iostream>
#include <cmath>
#include "e.cpp"
#include "rk2d.cpp"
#include "rk2t.cpp"
#include "rk4.cpp"

using namespace std;

int main() {
    
    double x;        // Initial x
    double y;        // Initial y
    double v;		// Initial y'
    
    double h;         // Step size
    int numSteps;
    double x0;
    double y0;
    double v0;
    cout << "Vvedite X0: ";
    cin >> x0;
    cout << "Vvedite Y0: ";
    cin >> y0;
    cout << "Vvedite y': ";
    cin >> v0;
    cout << "Vvedite kolich steps: ";
    cin >> numSteps;
    cout << "Vvedite razmer shaga h: ";
    cin >> h;
    
    x=x0;
    v=v0;
    y=y0;
    cout << "Runge4 define: y(" << x << ") = " << y << endl;
    for (int i = 0; i < numSteps; ++i) {
        rungeKutta4(x, y, v, h);
        x += h;
        cout << "step  " << i + 1 << ": y(" << x << ") = " << y << ", y'(" << x << ") = " << v << endl;
    }
    x=x0;
    v=v0;
    y=y0;
    cout << "Runge2 time define : y(" << x << ") = " << y << endl;
    for (int i = 0; i < numSteps; ++i) {
        rungeKutta2time(x, y, v, h);
        x += h;
        cout << "step  " << i + 1 << ": y(" << x << ") = " << y << ", y'(" << x << ") = " << v << endl;
    }
    x=x0;
    v=v0;
    y=y0;
    cout << "Runge2 dif define: y(" << x << ") = " << y << endl;
    for (int i = 0; i < numSteps; ++i) {
        rungeKutta2diff(x, y, v, h);
        x += h;
        cout << "step  " << i + 1 << ": y(" << x << ") = " << y << ", y'(" << x << ") = " << v << endl;
    }
    x=x0;
    v=v0;
    y=y0;
    cout << "Eler: y(" << x << ") = " << y << endl;
    for (int i = 0; i < numSteps; ++i) {
        euler(x, y, v, h);
        x += h;
        cout << "step " << i + 1 << ": y(" << x << ") = " << y << ", y'(" << x << ") = " << v << endl;
    }

	system("pause");
    return 0;
}
