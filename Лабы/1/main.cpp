#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

void print(double** mtrx, int n, int m)
{
	cout.setf(ios::right | ios::fixed);
	cout.precision(2);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << setw(10) << mtrx[i][j];
    
		cout << "\n";
	}
	cout << "\n";
}

void gauss(double** mtrx, double* answ, int n, int m)
{
	double multiplier;
	for (int i = 0; i < n; i++) 
	{
		for (int j = n; j >= i; j--)
			mtrx[i][j] /= mtrx[i][i];
      
		for (int j = i + 1; j < n; j++)
		{
			multiplier = mtrx[j][i];
			for (int k = n; k >= i; k--)
        mtrx[j][k] -= multiplier * mtrx[i][k]; 
          cout << " " << " " << " " << "zanylyaem element" << " " << i+1 << " " << j+1;
          cout << "\n";
		      print(mtrx, n, m);
		}
		cout << "\n      zanulili " << i + 1 << "-i stolbec\n";
    cout << "\n";
		print(mtrx, n, m);
	}

	answ[n - 1] = mtrx[n - 1][n];
	for (int i = n - 2; i >= 0; i--)
	{
		answ[i] = mtrx[i][n];
		for (int j = i + 1; j < n; j++)
			answ[i] -= mtrx[i][j] * answ[j];
	}
}

void gaussMod(double** mtrx, double* answ, int n, int m)
{
	double multiplier;

	for (int i = 0; i < n; i++)
	{
		double max = abs(mtrx[i][i]);
		int index = i;
		for(int j = i + 1; j < n; j++)
			if (max < abs(mtrx[j][i]))
			{
				max = abs(mtrx[j][i]);
				index = j;
			}
		
		if (index != i)
		{
			cout << "      pomenyal " << i + 1 << "-u i " << index + 1 << "-u stroki\n";
			for (int j = 0; j < m; j++)
				swap(mtrx[i][j], mtrx[index][j]);
			print(mtrx, n, m);
		}
    else {cout << "ne pomenyalos";}

		for (int j = n; j >= i; j--)
			mtrx[i][j] /= mtrx[i][i];
		for (int j = i + 1; j < n; j++)
		{
			multiplier = mtrx[j][i];
			for (int k = n; k >= i; k--)
				mtrx[j][k] -= multiplier * mtrx[i][k];
		}
		cout << "\n      zanulili " << i + 1 << "-i stolbec\n";
		print(mtrx, n, m);
	}

	answ[n - 1] = mtrx[n - 1][n];
	for (int i = n - 2; i >= 0; i--)
	{
		answ[i] = mtrx[i][n];
		for (int j = i + 1; j < n; j++)
			answ[i] -= mtrx[i][j] * answ[j];
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	ifstream read("matrix.dat");
	int n, m, flag;
	read >> n >> m;

	double** matrix = new double* [n];
	double* answers = new double [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new double[m];
		for (int j = 0; j < m; j++)
			read >> matrix[i][j];
	}
	read.close();

	cout << "1 - obich. metod G\n2 - Mod. metod G\n>> ";
	cin >> flag;

	cout << "      Mmatrix:\n";
	print(matrix, n, m);
	flag == 1 ? gauss(matrix, answers, n, m) : gaussMod(matrix, answers, n, m);
	cout << "      Matrix posle preobrazovaniya :\n";
	print(matrix, n, m);
	cout << "      otveti:\n";
	for (int i = 0; i < n; i++)
		cout << "      X[" << i + 1 << "] = " << answers[i] << "\n";
	cout << "\n";

	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] answers;
  
	return 0;
}