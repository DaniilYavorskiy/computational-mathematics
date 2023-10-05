#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

void ObrabotkaStroki(double**& Matrix, int sizeOfMatrix, int i, double rowFactor) {
    for (int j = 0; j < 4; j++) {
        Matrix[i][j] = Matrix[i][j] - Matrix[i - 1][j] * rowFactor;
    }
}

int main() {
    char buffer[256];
    int countOfRows = 0;
    int sizeOfMatrix = 0;

    ifstream fileOfMatrix("matrix.txt");
    if (fileOfMatrix.is_open()) {
        while (!fileOfMatrix.eof()) {
            countOfRows++;
            fileOfMatrix.getline(buffer, 256);
        }
        cout << countOfRows << endl;
        fileOfMatrix.close();
    }

    sizeOfMatrix = countOfRows;
    double** Matrix = new double* [sizeOfMatrix];
    double* B = new double[sizeOfMatrix];
    double* cloneB = new double[sizeOfMatrix];

    for (int i = 0; i < sizeOfMatrix; i++) {
        Matrix[i] = new double[sizeOfMatrix + 1];
    }

    ifstream myfile("matrix.txt");
    if (myfile.is_open()) {

        for (int i = 0; i < sizeOfMatrix; i++) {
            for (int j = 0; j < sizeOfMatrix + 1; j++) {
                myfile >> Matrix[i][j];
                cout << Matrix[i][j] << "  ";
            }
            cout << endl;
        }
        myfile.close();
    }
    cout << endl;

    for (int i = 0; i < sizeOfMatrix; i++) {
        double k = Matrix[i][i];
        for (int j = 0; j <= sizeOfMatrix; j++) {
            Matrix[i][j] = Matrix[i][j] / k;
            cout << Matrix[i][j] << "  ";
        }
        cout << endl;
    }

    for (int i = 0; i < sizeOfMatrix; i++) {
        B[i] = 0;
        Matrix[i][i] = 0;
    }
    
    int deltaCheck = 0;
    double delta = 0.00001;

    float N = abs(log((delta * abs(1 - Matrix[0][sizeOfMatrix])) / Matrix[sizeOfMatrix - 1][sizeOfMatrix])) / (log(Matrix[0][sizeOfMatrix]))+1;
    
    for (int numberOfStep = 0; numberOfStep < N; numberOfStep++) {

        deltaCheck = 0;
        int flag = 0;
        double sumOfString = 0;
        for (int i = 0; i < sizeOfMatrix; i++) cloneB[i] = B[i];

        cout <<endl<< "Step: " << numberOfStep << " = "<<endl;

        for (int i = 0; i < sizeOfMatrix; i++) {
            cout << setw(5) << Matrix[i][sizeOfMatrix] << " ";
            cout << setw(4);
            if (sizeOfMatrix / 2 == i) {
                flag = 1;
                cout << "-  ";
            }
            else cout << "   ";

            for (int j = 0; j < sizeOfMatrix; j++) {
                cout << setw(4) << Matrix[i][j] << "  ";

                sumOfString = sumOfString + Matrix[i][j] * B[j];
            }

            if (flag == 1) cout << " *";
            else cout << "  ";

            cout << setw(8) << B[i];
            B[i] = Matrix[i][sizeOfMatrix] - sumOfString;
            if (flag == 1) cout << "  =";
            else cout << "   ";
            cout << setw(10) << B[i] << endl;
            flag = 0;
            sumOfString = 0;
        }

        for (int i = 0; i < sizeOfMatrix; i++) {
           if (((abs(B[i] - cloneB[i]))) < delta) deltaCheck++;
            cout << "x" << i << ": Delta: " << (abs(cloneB[i] - B[i])) << endl;
        }
        if (deltaCheck == sizeOfMatrix) cout << endl << "Tochnost dostignuta))" << endl;
        else  cout << endl << "Tochnost ne dostignuta" << endl;
    }
   

    for (int i = 0; i < sizeOfMatrix; i++) {
        delete[]Matrix[i];
    }
    delete[]Matrix;
    delete[]B;
    delete[]cloneB;

    return 0;
}

