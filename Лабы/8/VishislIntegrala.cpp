#include <iostream>
#include <math.h>
#define e  2.718281
#define E 0.001 
#define Integral 1.02814
using namespace std;
 
 
float f(float x){
    x = pow(e,x)/sqrt(1+pow(e,x));
    return x;
}
 
float integral(float a,float b)
{
    float i;
    float h=0.0,sint=0.0;
    
    
    cout<<"a = "<<a<<"  b = "<<b;
    
    h = ( b - a)/10000;
    i = a+h/2;
    
    cout<<"h = "<<h<<"  i = "<<i<<endl;
 
    while (i <= b)
    {
        sint+=f(i)*h;
        i+=h;
        if(fabs(sint-Integral)<E)
            break;
    }
    
    return sint;
     
    return 0;
}
 
 
int main(){
 
    cout<<"Integral raven: "<<integral(0,1);
     system("PAUSE");
return 0;    
}