#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

int factorial(int x){
	int result=1;
	for(int i = 1; i<=x; i++){
		result*=i;
	}
	return result;
}

double newton_interpolation(double x, double* x_vals, double* y_vals, int n, double h)
{
    double term = 1;
    double diff_table[n][n];
    
    for(int i =0; i<n;i++){
    	for(int j = 0; j<n;j++){
    		diff_table[j][i]=-1;
    	}
    }
    
    for(int i = 0; i<n;i++){
    	diff_table[0][i]=y_vals[i+1]-y_vals[i];
    }
    for(int i = 1; i<n; i++){
    	for(int j = 0; j<n-i;j++){
    		diff_table[i][j]=diff_table[i-1][j+1]-diff_table[i-1][j];
   		}
    }
    
//    for(int i =0; i<n;i++){
//    	for(int j = 0; j<n;j++){
//    		printf("%f ", diff_table[j][i]);
//    	}
//    	printf("\n");
//    }

	double q = (x-x_vals[n])/h;
	double qq=q;
	double result = y_vals[n];
	for(int i = n; i>0; i--){
		result += diff_table[n-i][i-1]*qq/factorial(n-i+1);
		qq*=(q+n-i+1);
	}
	
    return result;
}

double Function(double x) {
	return sqrt(x);
//	return 2*powf(x,3)-2*powf(x,2)+3*x-1;
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

void epsilon_usech(double x, int n, double h, double x0){
	n++;
	double x_vals[n+1], y_vals[n+1];
    for (int i = 0; i <= n; i++) {
		x_vals[i]=x0+i*h;
		y_vals[i]=Function(x_vals[i]);
    }
    
    double diff_table[n][n];
    
    for(int i =0; i<n;i++){
    	for(int j = 0; j<n;j++){
    		diff_table[j][i]=-1;
    	}
    }
    
    for(int i = 0; i<n;i++){
    	diff_table[0][i]=y_vals[i+1]-y_vals[i];
    }
    for(int i = 1; i<n; i++){
    	for(int j = 0; j<n-i;j++){
    		diff_table[i][j]=diff_table[i-1][j+1]-diff_table[i-1][j];
   		}
    }
    
//    for(int i =0; i<n;i++){
//    	for(int j = 0; j<n;j++){
//    		printf("diff_table[%d][%d]=%f ", j,i ,diff_table[j][i]);
//    	}
//    	printf("\n");
//    }

    double eps;
    double q = (x-x0)/h;
    double qq=q;
    for(int i = 1; i<n-1;i++){ //может быть i<n
    	qq*=q-i;
	}
	eps=diff_table[n-1][0]*y_vals[0]*qq/factorial(n);
	printf("Eps usech. = %f \n", eps);
}


int main() {
	
    double x0;
    double h;
    int n;
    
     cout << "Vvedite kolichestvo tochek n: ";
    cin >> n;
    cout << "Vvedite razmer shaga h: ";
    cin >> h;
    cout << "Vvedite nachalnyu tochky x0: ";
    cin >> x0;
    
    double xi, yi;
    cout << "Vvedite znachenie X, v kotorom naidetsya znachenie y: ";
    cin >> xi;
	
    //определение точек интерполяции
    double x_vals[n+1], y_vals[n+1];
    for (int i = 0; i <= n; i++) {
		x_vals[i]=x0+i*h;
		y_vals[i]=Function(x_vals[i]);
    }
    
    yi = newton_interpolation(xi, x_vals, y_vals, n, h);
    cout << "V tochke x = " << xi << " znachenie y = " << yi << endl;
    epsilon_usech(xi,n,h,x0);

    // рисование
    int window_width=1080, window_height=720;
    initwindow(window_width, window_height);
    
    double x_step = 0.1;
    int x_min = 0, x_max = 7;
    int scale = 100; // пиксели на 1 единицу
	int x_shift = (window_width/2)-((x_min+x_max)/2)*scale;
	int y_shift = window_height/2;
	
	double x_val = x_min, y_val;
    draw_axis(x_shift, y_shift, scale);
    
    // рисование исходной функции
    setcolor(BLUE);
    for (int i = 0; i < (x_max - x_min) / x_step; i++) {
        y_val = Function(x_val);
        int x1 = x_val * scale + x_shift;
        int y1 = y_shift - y_val * scale;
        int x2 = (x_val + x_step) * scale + x_shift;
        int y2 = y_shift - Function(x_val+x_step) * scale;
        line(x1, y1, x2, y2);
        x_val += x_step;
    }

	
    // рисование интерполируемой функции
    x_val=x_min;
    setcolor(YELLOW);
    for (int i = 0; i < (x_max - x_min) / x_step; i++) {
        y_val = newton_interpolation(x_val, x_vals, y_vals, n, h);
        int x1 = x_val * scale + x_shift;
        int y1 = y_shift - y_val * scale;
        int x2 = (x_val + x_step) * scale + x_shift;
        int y2 = y_shift - newton_interpolation(x_val+x_step, x_vals, y_vals, n, h) * scale;
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
