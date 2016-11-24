#include <math.h>
#include <iostream>
#include <algorithm>

const double EPS = 0.01;

using namespace std;

double f(double x) {
	return (exp(x)*sqrt(1 - x) - 0.1);
}

double f1(double x) {
	return ((exp(x)*(1 - 2 * x)) / (2 * sqrt(1 - x)));
}

double f2(double x) {
	return (-(exp(x)*((-4)*x*x + 4 * x + 1)) / (4 * (pow((1 - x), 1.5))));
}

bool checkExactness(double xN, double EPS, double const_m1) {
	return fabs(f(xN)) / const_m1 >= EPS;
}

void ChordMethod(double xN1, double const_m1, double C) {
	double xN = xN1;
	double xN_1 = 0;
	double EPSi = EPS, EPSi_1 = EPS;
	int z = 1;
	int i = 0;

	cout << "CountI\tEPSi\tRoot\t  Tolerance\n";
	for (; z <= 4; z++) {
		EPSi = EPSi_1 / pow(10, 3);
		EPSi_1 = EPSi;
		do {
			xN_1 = xN - (f(xN) / (f(xN) - f(C)))*(xN - C);
			xN = xN_1;
			i++;
		} while (checkExactness(xN, EPSi, const_m1));
		cout << i << "\t" << EPSi << "\t" << xN << "  " << fabs(f(xN)) / EPSi << "\n";
	}
}


bool checkExactness(double x, double xn, double EPS, double Q) {
	return fabs(x - xn) >= EPS*(1 - Q) / Q;
}

void IterativeProcess(double xn, double LAMDA, double Q) {
	double x, Xn;
	double EPSi = EPS, EPSi_1 = EPS;
	int i = 0;
	int z = 1;

	cout << "CountI\tEPSi\tRoot\t  Tolerance\n";
	for (; z <= 4; z++) {
		EPSi = EPSi_1 / pow(10, 3);
		EPSi_1 = EPSi;
		Xn = xn;
		do {
			x = Xn;
			if (f1(x) > 0)
				Xn = x - LAMDA*f(x);
			else
				Xn = x + LAMDA*f(x);
			i++;
		} while (checkExactness(x, Xn, EPSi, Q));
		cout << i << "\t" << EPSi << "\t" << Xn << "  " << ((1 - Q)*EPSi) / Q << "\n";
	}
}


void solution(double a, double b) {
	double xn = (a + b) / 2.0;

	long double m1 = min(abs(f1(a)), abs(f1(b)));
	long double M1 = max(abs(f1(a)), abs(f1(b)));
	
	long double LAMDA = 1.0 / M1;
	long double q = 1 - m1 / M1;
	long double C = 0;

	for (long double i = a; a <= b; i += 0.0001) {
		if (f(i)*f2(i) > 0) {
			C = i;
			break;
		}
	}

	cout << "Iterative Process:" << endl;
	IterativeProcess(xn, LAMDA, q);
	cout << endl << "Chord Method:" << endl;
	ChordMethod(xn, m1, C);
}

int main() {
	cout << "For [0.8, 0.9999]:" << endl;
	solution(0.8, 0.9999);
	cout << endl << endl << "For [-5, -2]:" << endl;
	solution(-5, -2);
	return 0;
}