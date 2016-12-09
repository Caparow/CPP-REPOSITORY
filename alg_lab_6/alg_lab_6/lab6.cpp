#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;


const int N = 30;
const int A = 3;
const int B = 12;

typedef double matrix[N + 1][N + 2];
typedef double vect[N + 1];

double F(double x){	return 0.025*exp(x-5)*sin(2.5*x); }

void GenerateSLAR(double(*f)(double), int n, double a, double b, matrix& res)
{
	double h = (b - a) / n;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n + 1; j++)
			res[i][j] = 0;

	for (int i = 1; i < n; i++)
	{
		if (i > 0) res[i][i - 1] = h;
		res[i][i] = 4 * h;
		if (i < n) res[i][i + 1] = h;
		double xm1 = a + h * (i - 1);
		double x1 = a + h * i;
		double xp1 = a + h * (i + 1);
		res[i][n + 1] = 6 * ((f(xp1) + f(xm1) - 2 * f(x1)) / h);
	}
	res[0][0] = 1;
	res[0][n + 1] = 0;
	res[n][n] = 1;
	res[n][n + 1] = 0;
}

void CalcDB(double(*f)(double), const vect& vC, vect& vD, vect& vB, vect& vA, int n, double a, double b, vect& x)
{
	x[0] = a;
	vA[0] = f(a);
	double h = (b - a) / n;
	for (int i = 1; i <= n; i++)
	{
		x[i] = a + (i * (b - a)) / n;
		vA[i] = f(a + ((i*(b - a)) / n));
		vD[i] = (vC[i] - vC[i - 1]) / h;
		vB[i] = h*vC[i] / 2 - h*h*vD[i] / 6 + (f(a + h * i) - f(a + h * (i - 1))) / h;
	}
}

void CopyMatrix(matrix& dest, const matrix src, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= n; j++)
			dest[i][j] = src[i][j];
}

bool GaussianElimination(const matrix SLAR, int n, vect& X)
{
	matrix a;
	CopyMatrix(a, SLAR, n);

	for (int k = 0; k < n; k++)
	{
		if (a[k, k] == 0)
		{
			cout << "Divide by zero!" << endl;
			return false;
		}

		double e = a[k][k];
		for (int j = k; j <= n; j++)
			a[k][j] = a[k][j] / e;

		for (int i = k + 1; i < n; i++)
		{
			e = a[i][k];
			for (int j = 0; j <= n; j++)
				a[i][j] = a[i][j] - a[k][j] * e;
		}
	}

	for (int i = n - 1; i >= 0; i--)
	{
		double sub = 0;
		for (int j = i + 1; j < n; j++)
			sub += a[i][j] * X[j];

		X[i] = a[i][n] - sub;
	}
	return true;
}


void PrintVect(vect const X, int n)
{
	for (int i = 0; i < n; i++)
		cout << "X[" << i << "]=" << X[i] << endl;
	cout << endl;
}

void PrintParth(double c, double xi)
{
	if (c == 0) return;

	if (c < 0)
		cout << " - " << 0.0 + abs(c) << "*";
	else
		cout << " + " << c << "*";


	if (xi == 0)
		cout << "x";
	else
		if (xi < 0)
			cout << "(x + " << 0.0 + abs(xi) << ")";
		else
			cout << "(x - " << xi << ")";
}

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
		tmp *=-( 0.0 + abs(c));
	else
		tmp *= c;

	return tmp;
}

void PrintSpline(vect const vA, vect const vB, vect const vC, vect const vD, int n, double a, double b)
{
	for (int i = 1; i <= n; i++)
	{
		double xi = a + (i * (b - a)) / n;
		cout << "s" << i << "(x)=" << vA[i];
		PrintParth(vB[i], xi);
		PrintParth(vC[i] / 2., xi);
		cout << "^2 ";
		PrintParth(vD[i] / 6., xi);
		cout << "^3,  [" << a + ((i - 1) * (b - a)) / n << ", " << a + (i * (b - a)) / n << "]" << endl;
	}

	ofstream table("table.csv");
	double tmp = 0;
	for (int i = 1; i <= n; ++i) {
		double xi = a + (i * (b - a)) / n;
		for (double x = a + ((i - 1) * (b - a)) / n; x <= a + (i * (b - a)) / n; x += 0.05) {
			tmp += vA[i];
			tmp += CalcSt(vB[i], xi, x, 1);
			tmp += CalcSt(vC[i] / 2., xi, x, 2);
			tmp += CalcSt(vD[i] / 6., xi, x, 3);
			table << x << ";" << tmp << endl;
			tmp = 0;
		}
	}
	table.close();
	cout << endl;
}

int main()
{
	matrix SLAR;
	GenerateSLAR(F, N, A, B, SLAR);

	vect c, d, b, a, x;
	GaussianElimination(SLAR, N + 1, c);
	CalcDB(F, c, d, b, a, N, A, B, x);

	PrintSpline(a, b, c, d, N, A, B);
	return 0;
}
