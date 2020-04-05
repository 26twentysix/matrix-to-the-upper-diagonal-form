#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

void ShowVector(int n, double* vec) {
	for (int i = 0; i < n; i++) {
		cout << setw(8) << vec[i] << " ";
	}
	cout << endl;
}

void PryamoiHod(int n, double** a, double* b) {
	double v;
	for (int k = 0, i, j, im; k < n - 1; k++) {
		im = k;
		for (i = k + 1; i < n; i++) {
			if (fabs(a[im][k]) < fabs(a[i][k])) {
				im = i;
			}
		}
		if (im != k) {
			for (j = 0; j < n; j++) {
				v = a[im][j];
				a[im][j] = a[k][j];
				a[k][j] = v;
			}
			v = b[im];
			b[im] = b[k];
			b[k] = v;
		}
		for (i = k + 1; i < n; i++) {
			v = 1.0 * a[i][k] / a[k][k];
			a[i][k] = 0;
			b[i] = b[i] - v * b[k];
			if (v != 0) {
				for (j = k + 1; j < n; j++) {
					a[i][j] = a[i][j] - v * a[k][j];
				}
			}
		}
	}
}

void ObratniHod(int n, double** a, double* b, double* x) {
	double s = 0;
	x[n - 1] = 1.0 * b[n - 1] / a[n - 1][n - 1];
	for (int i = n - 2, j; 0 <= i; i--) {
		s = 0;
		for (j = i + 1; j < n; j++) {
			s = s + a[i][j] * x[j];
		}
		x[i] = 1.0 * (b[i] - s) / a[i][i];
	}
}

int main() {
	setlocale(0, "");
	int i, j, n;
	double** a, * b, * x;
	cout << "Введите количество уравнений: " << endl;
	cin >> n;
	a = new double* [n];
	b = new double [n];
	x = new double[n];
	for (i = 0; i < n; i++) {
		a[i] = new double[n];
		for (j = 0; j < n; j++) {
			cout << "Элемент [" << i+1 << "][" << j+1 << "] = ";
			cin >> a[i][j];
		}
	}
	for (i = 0; i < n; i++)
	{
		cout << "Свободный член [" << i+1 << "] = ";
		cin >> b[i];
	}
	cout << endl << "Матрица А: " << endl;
	for (i = 0; i < n; i++) {
		ShowVector(n, a[i]);
	}
	cout << "Вектор B: " << endl;
	ShowVector(n, b);
	cout << endl << "Решение методом Гаусса" << endl;
	PryamoiHod(n, a, b);
	cout << "Прямой ход " << endl;//Прямой ход
	cout << endl << "Матрица А: " << endl;
	for (i = 0; i < n; i++) {
		ShowVector(n, a[i]);
	}
	cout << "Вектор B: " << endl;
	ShowVector(n, b);
	ObratniHod(n, a, b, x);
	cout << "Обратный ход " << endl;//Обратный ход
	cout << endl << "Матрица А: " << endl;
	for (i = 0; i < n; i++) {
		ShowVector(n, a[i]);
	}
	cout << "Вектор B: " << endl;
	ShowVector(n, b);
	cout << "Решение: " << endl;
	ShowVector(n, x);
	delete[] a;
	delete[] b;
	delete[] x;
	return 0;
}
