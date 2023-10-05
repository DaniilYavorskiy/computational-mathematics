#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

//x^2 - x - 1 [1; 2]

int n = 0;

double function (double x) {
	return (x * x) - x - 1;
}

double proizvodnaya (double x) {
	return 2 * x - 1;
}

int main() {
	cout << "Metod Nutona:" << endl;
	double x0 = 2;
	double exp = 0.000000001;
	double a = 1, b = 2, c = 0;
	double x = x0 - function(x0) / proizvodnaya(x0);
	while (abs(x - x0) > exp) {
		x0 = x;
		x = x0 - function(x) / proizvodnaya(x);
		n++;
		cout << "Step N" << n << ": x = " << x << endl;
	}
	
	n = 0;	
	cout << "\nMetod Polovinnogo Deleniya\n[" << a << "; " << b << "]" << endl;
	while (abs(a - b) > exp) {
		c = (a + b)/2;
		if (function(a) * function(c) > 0)
		a = c;
		else b = c;
		n++;
		cout << "Step N" << n << ": x = " << c << " [" << a << "; " << b << "]" << endl;
	}

	double C = 0;
	n = 0; a = 1, b = 2, c = b;
	cout << "\nMetod Hord:" << endl;
	while (abs(c - C) > exp) {
		C = c;
		c = (a * function(b) - b * function(a)) / (function(b) - function(a));
		if (function(a) * function(c) > 0)
		a = c;
		else b = c;	
		n++;
		cout << "Step N" << n << ": x = " << c << " [" << a << " ; " << b << "]" << endl;
	}
}