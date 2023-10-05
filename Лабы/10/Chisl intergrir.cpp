#include <iostream>

using namespace std;

class function {
private:

    double a;
    double b;
    double (*funk)(double);

public:

    function(double(*funk)(double)) {

        a = 0;
        b = 0;
        this->funk = funk;

    }

    ~function() {}

    double Integrate(double a, double b, double e, double actual, int* count, double* h) {

        double step = b - a;
        double resoult = 0;
        this->a = a;
        this->b = b;
        double s = 0;

        while (abs(actual - resoult) > 3 * e) {

            resoult = 0;

            for (double i = a; i <= b - step; i += step) {
                resoult += step * (abs(funk(i)) + abs(funk(i + step))) / 2;
            }
            step /= 2;
            s++;
        }
        *count = s;
        *h = step;

        return resoult;
    }
    double formulaSimpson(double a, double b, double e, double actual, int* count, double* h) {

        double step = b - a;
        this->a = a;
        this->b = b;
        double resoult = 0;
        int s = 0;

        while (abs(actual - resoult) > e) {

            resoult = 0;
            for (double i = a + step; i <= b; i += 2 * step) {
                resoult += 2 * step * (abs(funk(i - step)) / 6 + 2 * abs(funk(i)) / 3 + abs(funk(i + step) / 6));
            }
            step /= 2;
            s++;
        }
        *count = s;
        *h = step;

        return resoult;
    }
};

double funk(double x) {
    return (1/x);
}

int main()
{
    function inter(funk);
    double answerTrap;
    double answerSimp;
    double h;
    double h1;
    int count = 0;
    int count2 = 0;

    answerTrap = inter.Integrate(1, 2, 0.000001, 0.693147, &count2, &h);
    answerSimp = inter.formulaSimpson(1, 2, 0.000001, 0.693147, &count, &h1);
    cout << "answer: " << answerSimp << "  steps count: " << count2 << " length of steps: " << h << "  |Trap|"<< endl;
    cout << "answer: " << answerTrap << "  steps count: " << count << " length of steps: " << h1 <<"  |Simpson|" << endl;
    return 0;
}