#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// Функция для интерполяции
double Function(double x) {
    return sqrt(x);
}

// интерполирую в точке x, xvals и yvals - точки данных
double aitken(double x, double x_vals[], double y_vals[], int n) {
    double F[n][n];

    // создаю 1-ый столбец таблицы Эйткена
    for (int i = 0; i < n; i++) {
        F[i][0] = y_vals[i];
    }

    // строю оставшиеся таблицы
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            F[i][j] = ((x - x_vals[i]) * F[i+1][j-1] - (x - x_vals[i+j]) * F[i][j-1]) / (x_vals[i+j] - x_vals[i]);
        }
    }
    
    return F[0][n-1];
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

int main() {
	
	int n;
    double x_vals[20], y_vals[20];
    double x0;
    double h;
    cout << "Vvedite kolichestvo tochek n: ";
    cin >> n;
    cout << "Vvedite razmer shaga h: ";
    cin >> h;
    cout << "Vvedite nachalnyu tochky x0: ";
    cin >> x0;
    
    n++;

    for (int i = 0; i <= n; i++) {
		x_vals[i]=x0+(i+1)*h;
		y_vals[i]=Function(x_vals[i]);
    }
    
    double xi, yi;
    cout << "Vvedite znachenie X, v kotorom naidetsya znachenie y: ";
    cin >> xi;

    yi = aitken(xi, x_vals, y_vals, n);
    cout << "V tochke x = " << xi << " znachenie y = " << yi << endl;

    
    // Свойства графика
    int window_width=1080, window_height=720;
    initwindow(window_width, window_height);
    
    setcolor(WHITE);
    double x_step = 0.01;
    int x_min = 0, x_max = 10, y_min = y_vals[0], y_max = y_vals[n];
    int scale = 100; // пиксели на 1 единицу
	int x_shift = (window_width/2)-((x_min+x_max)/2)*scale;
	int y_shift = window_height/2;
	
    double x_val = x_min, y_val;
    draw_axis(x_shift, y_shift, scale);
    
    //рисование интерполируемой функции
    setcolor(YELLOW);
    for (int i = 0; i < (x_max - x_min) / x_step; i++) {
        y_val = aitken(x_val, x_vals, y_vals, n);
        int x1 = x_val * scale + x_shift;
        int y1 = y_shift - y_val * scale;
        int x2 = (x_val + x_step) * scale + x_shift;
        int y2 = y_shift - aitken(x_val, x_vals, y_vals, n) * scale;
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

    setcolor(RED);
    for (int i = 0; i < n; i++) {
        int x1 = x_vals[i] * scale + x_shift;
        int y1 = y_shift - y_vals[i] * scale;
        circle(x1, y1, 3);
    }

    getch();
    closegraph();
    return 0;
}

