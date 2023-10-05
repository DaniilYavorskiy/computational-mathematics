#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

double lagrange_interpolation(double x[], double y[], int n, double xi, int outFlag) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y[i];

        for (int j = 0; j < n; j++) {
            if (i != j) {
                term = term * (xi - x[j]) / (x[i] - x[j]);
            }
        }

        result += term;
        if(outFlag)
        	cout << "Pogreshnost: "<<result<<endl; 
    }

    return result;
}

void draw_axis(int x0, int y0, int scale){
	setcolor(WHITE);
	line(x0-1000, y0, x0+1000, y0);
	line(x0, y0-1000, x0, y0+1000);
	for(int i = 1; i<20; i++){
		line(x0+i*scale, y0-5, x0+i*scale, y0+5); 
		
		line(x0-i*scale, y0-5, x0-i*scale, y0+5); 
		
		line(x0-5, y0-i*scale, x0+5, y0-i*scale); 
		
		line(x0-5, y0+i*scale, x0+5, y0+i*scale); 
	}
}

double Function(double x){
	return sqrt(x);	
};

int main() {
    int n;
    double x[20], y[20], xi, yi;
    double x0;
    double h;
    cout << "Vvedite kolichestvo tochek n: ";
    cin >> n;
    cout << "Vvedite razmer shaga h: ";
    cin >> h;
    cout << "Vvedite nachalnyu tochky x0: ";
    cin >> x0;
//    cout << "Vvedite tochki:\n";
	n++;
    for (int i = 0; i <= n; i++) {
//        cout << "x[" << i << "] = ";
//        cin >> x[i];
//        cout << "y[" << i << "] = ";
//        cin >> y[i];
		x[i]=x0+(i+1)*h;
		y[i]=Function(x[i]);
    }
	
    cout << "Vvedite znachenie X, v kotorom naidetsya znachenie y: ";
    cin >> xi;

    yi = lagrange_interpolation(x, y, n, xi,1);
    cout << "V tochke x = " << xi << " znachenie y = " << yi << endl;

    // рисование
    int window_width=1080, window_height=720;
    initwindow(window_width, window_height);
    
    double x_step = 0.01;
    int x_min = 0, x_max = 10, y_min = y[0], y_max = y[n-1];
    int scale = 100; // пиксели на 1 единицу
	int x_shift = (window_width/2)-((x_min+x_max)/2)*scale;
	int y_shift = window_height/2;
	
    double x_val = x_min, y_val;
    draw_axis(x_shift, y_shift, scale);
    
    //рисование интерполируемой функции
    setcolor(YELLOW);
    for (int i = 0; i < (x_max - x_min) / x_step; i++) {
        y_val = lagrange_interpolation(x, y, n, x_val, 0);
        int x1 = x_val * scale + x_shift;
        int y1 = y_shift - y_val * scale;
        int x2 = (x_val + x_step) * scale + x_shift;
        int y2 = y_shift - lagrange_interpolation(x, y, n, x_val + x_step,0) * scale;
        line(x1, y1, x2, y2);
        x_val += x_step;
    }
    
    //рисование исходной функции
    setcolor(WHITE);
    x_val = x_min;
    for (int i = 0; i < (x_max - x_min) / x_step; i++) {
        y_val = Function(x_val);
        int x1 = x_val * scale + x_shift;
        int y1 = y_shift - y_val * scale;
        int x2 = (x_val + x_step) * scale + x_shift;
        int y2 = y_shift - Function(x_val+x_step) * scale;
        line(x1, y1, x2, y2);
        x_val += x_step;
    }

    setcolor(WHITE);
    for (int i = 0; i < n; i++) {
        int x1 = x[i] * scale + x_shift;
        int y1 = y_shift - y[i] * scale;
        circle(x1, y1, 10);
    }

    getch();
    closegraph();
    return 0;
}
