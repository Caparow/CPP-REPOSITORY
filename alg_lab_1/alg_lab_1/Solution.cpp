#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Windows.h>

using namespace std;


int getM(long double x) {
	int temp = 1;
	while (x > 2) {
		x = x / 2;
		temp++;
	}
	return (temp);
}

long double calcL(long double x, int k, long double l) {
	long double temp = 1;
	long double z = 0;
	long double a = 0;
	int m = 0;

	m = getM(x);
	z = x / exp(m*log(2));
	a = (1 - z) / (1 + z);
	if (l == 1)
		return a;
	
	temp = l*(2 * (k - 1) - 1)*a*a / (2 * k - 1);

	return (temp);
}

long double calcR(int n, long double eps, long double x, long double l) {
	long double temp;
	temp = l / 4 * eps;
	return temp;
}

int main() {
	const long double a_start = 0.1;
	const long double b_end = 15;
	long double x = (a_start + b_end) / 2;

//--------------------------task 1-----------------------------------------------------------
	long double absolute_ln = log(x);
	long double temp = 0;
	long double l = 1;
	int n = 1;
	int temp_n = 0;
	temp = getM(x) * M_LN2;

	cout << setw(6) << "Eps" << setw(5) << "N" << setw(17) << "Abs" << setw(17) << "Rn" << endl;

	for (long double eps = 1.0e-2; eps > 1.0e-15; eps /= 1000.0) {
		while (calcL(x, n, l) > 4 * eps) {
			l = calcL(x, n, l);
			temp = temp - 2 * l;
			n++;
		}
		if (eps == 1.0e-8)
			temp_n = n;
		printf("%6g  %3d  %15g  %15g\n", eps, n-1, abs(absolute_ln - temp), calcR(n, x, eps, l));
	}
	cout << endl << endl;

//--------------------------task 2-----------------------------------------------------------
	long double h = (b_end - a_start) / 10;
	temp = 0;
	l = 1;

	cout << setw(6) << "X" << setw(17) << "Abs" << setw(17) << "Rn" << endl;

	for (int i = 0; i <= 10; ++i) {
		x = a_start + h*i;
		temp = getM(x) * M_LN2;
		l = 1;
		for (int n = 1; n < temp_n; ++n) {
			l = calcL(x, n, l);
			temp -= 2 * l;
		}
		printf("%6g  %15g  %15g\n", x, abs(log(x) - temp), calcR(temp_n, x, 1.0e-08, l));
	}

	return 0;
}

