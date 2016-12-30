#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

struct spline
{
	double a, b, c, d, x;
};

const int N = 100; //колличество кубических сплайнов на функцию
const int A = 3; 
const int B = 12;

//интерполируемая функция
double f(double x) { return 0.025*exp(x - 5)*sin(2.5*x); }

//создание СЛАР для нахождения С коеффициентов
vector<vector<double>> GenSystem(int n, double a, double b) 
{
	vector<vector<double>> res;
	vector<double> tmp;
	double x, xp, xn;
	double h = (b - a) / n;

	for (int i = 0; i <= n + 1; ++i)
		tmp.push_back(0);
	for (int i = 0; i <= n; ++i)
		res.push_back(tmp);
	tmp.clear();

	for (int i = 1; i <= n; ++i)
	{
		res[i][i] = 2 * (h + h);
		res[i][i - 1] = h;
		res[i][i + 1] = h;
		x = a + h * i;
		xp = a + h * (i - 1);
		xn = a + h * (i + 1);
		res[i][i+1] = 6 * ((f(xn) + f(xp) - 2 * f(x)) / h);
	}
	res[0][0] = 1;
	res[0][n + 1] = 0;
	res[n][n] = 1;
	res[n][n + 1] = 0;

	return res;
}

//решение СЛАР схемой единого деления (исключение Гаусса)(метод взят из 5ой лабораторной работы)
vector<double> GaussEllimination(vector< vector<double> > A) {
	int n = A.size();

	for (int i = 0; i<n; i++) {
		// Search for maximum in this column
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k<n + 1; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j<n + 1; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	// Solve equation Ax=b for an upper triangular matrix A
	vector<double> x(n);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = A[i][n] / A[i][i];
		for (int k = i - 1; k >= 0; k--) {
			A[k][n] -= A[k][i] * x[i];
		}
	}
	return x;
}

//расчет коеффициентов сплайнов
vector<spline> GenSpline(vector<double> c, int n, double a, double b)
{
	vector<spline> res;
	double h = (b - a) / n;
	spline tmp;
	res.push_back(tmp);

	for (int i = 1; i <= N; ++i)
	{
		spline tmp;
		tmp.x = a + i*h;
		tmp.c = c[i];
		tmp.a = f(tmp.x);
		tmp.d = (c[i] - c[i - 1]) / h;
		tmp.b = h*c[i] / 2 - h*h*tmp.d / 6 + (f(tmp.x) - f(tmp.x - h)) / h;
		res.push_back(tmp);
	}

	return res;
}

//расчет отдельного члена функции сплайна
double CalcSt(double c, double xi, double x, int st) {
	double tmp = 0;
	if (xi == 0)
		tmp = x;
	else
		if (xi < 0)
			tmp = (x + 0.0 + abs(xi));
		else
			tmp = (x - xi);

	tmp = pow(tmp, st);

	if (c < 0)
		tmp *= -(0.0 + abs(c));
	else
		tmp *= c;

	return tmp;
}

void CalcSplineF(vector<spline> sp, int n, double a, double b)
{
	double h = (b - a) / n;
	ofstream table("table.csv");
	double tmp = 0;

	for (int i = 1; i < n; ++i)
	{
		double xi = a + (i * (b - a)) / n;
		for (double x = a + (i - 1)*h + h / 5; x <= a + i*h + h / 5; x += h / 2) // '+h/5' для расчета не в узлах интерполяции
		{
			tmp += sp[i].a;
			tmp += CalcSt(sp[i].b, xi, x, 1);
			tmp += CalcSt(sp[i].c / 2., xi, x, 2);
			tmp += CalcSt(sp[i].d / 6., xi, x, 3);
			table << x << ";" << tmp << endl;
			tmp = 0;
		}
	}
	table.close();
}

int main()
{
	cout << "Generating system..." << endl;
	vector<vector<double>> mat = GenSystem(N, A, B);

	cout << "Finding C coeff..." << endl;
	vector<double> c = GaussEllimination(mat); 

	cout << "Generating spline functions..." << endl;
	vector<spline> sp = GenSpline(c, N, A, B);

	cout << "Calculating spline functions..." << endl;
	CalcSplineF(sp, N, A, B);

	cout << "Interpolation function is ready in the 'table.csv' file." << endl << endl;

	return 0;
}