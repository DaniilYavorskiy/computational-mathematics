#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;
using namespace sf;

const int n = 4;
const double zoom = 40;

double func(double x, int i) {
	if (i == 0)
		return 1;
	else if (i == 1)
		return x;
	else
		return x * x;
}

double polynomial(double* x, double* y, double z, int f) {
	double** mat = new double* [n - 1];
	for (int i = 0; i < n - 1; i++)
		mat[i] = new double[n];
	double res = 0;

	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n; j++)
			mat[i][j] = 0;

	for (int s = 0; s < n; s++) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++)
				mat[i][j] += func(x[s], i) * func(x[s], j);
			mat[i][n - 1] += func(x[s], i) * y[s];
		}
	}

	for (int i = 0; i < n - 1; i++) {

		int max = i;
		for (int j = i + 1; j < n - 1; j++)
			if (abs(mat[max][i]) < abs(mat[j][i]))
				max = j;
		double* temp = mat[max];
		mat[max] = mat[i];
		mat[i] = temp;

		double cof;
		for (int j = i + 1; j < n - 1; j++) {
			cof = mat[j][i] / mat[i][i] * (-1);

			for (int t = 0; t < n; t++)
				mat[j][t] += cof * mat[i][t];
		}
	}

	//Обратный ход
	for (int i = n - 2; i > -1; i--) {
		mat[i][n - 1] /= mat[i][i];
		mat[i][i] = 1;
		for (int j = i - 1; j > -1; j--)
			for (int t = n - 1; t > j; t--)
				mat[j][t] = mat[j][t] - mat[i][t] * mat[j][i];
	}

	for (int i = 0; i < n - 1; i++)
		res += mat[i][n - 1] * func(z, i);

	if (f == 1)
	cout << "\nYravnenie Approksimacii: y = " << mat[0][n - 1] << " + " << mat[1][n - 1]
		<< "x + " << mat[2][n - 1] << "x^2" << endl;

	return res;
}

int main() {
	double* x, * y; 
	double res, h = 1, f, f2, d = 0.01, x0 = 400, y0 = 400;

	x = new double[n];
	y = new double[n];
	x[0] = 1; y[0] = 2;
	x[1] = 2; y[1] = 5;
	x[2] = 4; y[2] = 6;
	x[3] = 6; y[3] = 7;

	res = polynomial(x, y, x[0], 1);

	RenderWindow window(VideoMode(800, 800), "Grafik");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	RectangleShape line[80];
	for (int i = 0; i < 80; i++) {
		line[i].setSize(Vector2f(1, 20));
		line[i].setFillColor(Color::Black);

		if (i < 40) {
			if (i < 20)
				line[i].setPosition(x0 - (i + 1) * zoom, y0 - 10);
			else
				line[i].setPosition(x0 + (i - 19) * zoom, y0 - 10);
		}
		else {
			line[i].setRotation(90);
			if (i < 60)
				line[i].setPosition(x0 + 10, y0 + (i - 60) * zoom);
			else
				line[i].setPosition(x0 + 10, y0 + (i - 59) * zoom);
		}
	}
	CircleShape circle(5);

	VertexArray axes(Lines, 4);
	axes[0].position = Vector2f(x0, 0);
	axes[1].position = Vector2f(x0, 800);
	axes[2].position = Vector2f(0, y0);
	axes[3].position = Vector2f(800, y0);
	axes[0].color = Color::Black;
	axes[1].color = Color::Black;
	axes[2].color = Color::Black;
	axes[3].color = Color::Black;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}

		window.clear(Color::White);

		window.draw(axes);

		for (int i = 0; i < 80; i++)
			window.draw(line[i]);

		f2 = polynomial(x, y, -10, 0);
		for (double i = -10; i < 10; i += d) {
			f = polynomial(x, y, i, 0);
			VertexArray chart(Lines, 2);
			chart[0].position = Vector2f(x0 + (i - d) * zoom, y0 - f2 * zoom);
			chart[1].position = Vector2f(x0 + i * zoom, y0 - f * zoom);
			chart[0].color = Color::Blue;
			chart[1].color = Color::Blue;
			window.draw(chart);
			f2 = f;
		}

		for (int i = 0; i < n; i++) {
			circle.setPosition(x0 - 5 + x[i] * zoom, y0 - 5 - y[i] * zoom);
			circle.setFillColor(Color::Red);
			window.draw(circle);
		}

		window.display();
	}

	delete[] x;
	delete[] y;

	return 0;
}