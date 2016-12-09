#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

const double a = 3;
const double b = 12;
const int m = 40;
const double eps = 1e-7;

typedef double(*myFunc) (const double, const int);
typedef double(*myT) (const double);

double f(const double x) { return 0.025*exp(x-5)*sin(2.5*x); }
double f0(double x) { return 1; }
double f1(double x) { return x; }

function<double(double)> tt(function<double(double)> f1, function<double(double)> f2) {
	function<double(double)> f = [f1, f2](const double x) {
		return 2*x*f2(x)-f1(x);
	};
	return f;
}

double T(double x, int n) {
	if (n == 0)
		return 1;
	else if (n == 1)
		return x;

	double res = 0;
	double Tn0 = 1;
	double Tn1 = x;

	for (int i = 1; i <= n-1; ++i) {
		res = 2 * x * Tn1 - Tn0;
		Tn0 = Tn1;
		Tn1 = res;
	}
	return res;
}

double integrate_cheb(const double a, const double b, const double eps, function<double(double)> f1, function<double(double)> f2) {

	int r = 2;
	int n = (int)ceil(pow(eps, -1 / (double)r));

	double I_n = 0, I_2n = 0;
	I_n += ((f1(a)*f2(a))+(f1(b)*f2(b))) / 2;
	double h = (b - a) / n;
	double x = a;
	for (int i = 1; i <= n-1 ; ++i) {
		x += h;
		I_n += f1(x)*f2(x);
	}
	I_2n = I_n;
	I_n *= h;

	return I_n;

	double tmp;
	tmp = I_n;
	do {
		n *= 2;
		h /= 2;
		I_n = tmp;
		double x = a + h;
		for (int i = 1; i <= n - 1; i += 2) {
			I_2n += f1(x)*f2(x);
			x += h + h;
		}
		tmp = I_2n*h;
	} while (abs(I_n - tmp) > 3 * eps);

	return tmp;
}

vector<double> gauss(vector< vector<double> > A) {
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

int main() {
	int tmp_m = 4;
	bool flag = false;
	long double delta = 100;
	double Pm = 0;
	double t_r;
	vector<double> pol;
	vector< vector<double> > matrix;
	vector<double> tmp;
	vector<double> alphas;
	vector<double> mat_r;
	vector<function<double(double)>> t_vec;
	t_vec.push_back(f0);
	t_vec.push_back(f1);

	for (int i = 2; i < tmp_m; ++i)
		t_vec.push_back(tt(t_vec[i - 2], t_vec[i - 1]));

	while (delta > 0.01) {
		delta = 0;
		pol.clear();
		t_vec.push_back(tt(t_vec[t_vec.size() - 2], t_vec[t_vec.size() - 1]));

		if (!flag) {
			flag = true;
			for (int i = 0; i < tmp_m; ++i) {
				for (int j = 0; j < tmp_m; ++j)
					tmp.push_back(integrate_cheb(a, b, eps, t_vec[i], t_vec[j]));
				t_r = integrate_cheb(a, b, eps, f, t_vec[i]);
				tmp.push_back(t_r);
				mat_r.push_back(t_r);
				matrix.push_back(tmp);
				tmp.clear();
			}
		}
		else {
			matrix.push_back(tmp);
			for (int i = 0; i < tmp_m; ++i)
				for (int j = matrix[i].size(); j < tmp_m; ++j)
					matrix[i].push_back(integrate_cheb(a, b, eps, t_vec[i], t_vec[j]));
			mat_r.push_back(integrate_cheb(a, b, eps, f, t_vec[tmp_m-1]));
			for (int i = 0; i < tmp_m; ++i)
				matrix[i].push_back(mat_r[i]);
		}		

		alphas = gauss(matrix);
		for (int i = 0; i < tmp_m; ++i)
			matrix[i].pop_back();
		for (double x = a; x <= b; x += 0.05) {
			for (int i = 0; i < tmp_m; ++i) 
				Pm += alphas[i] * T(x, i);
			delta += (f(x) - Pm)*(f(x) - Pm);
			pol.push_back(Pm);
			Pm = 0;
		}
		tmp_m++;
		delta = sqrt(delta / tmp_m);
		cout << "m = " << tmp_m-1 << "\t delta = " << delta << endl;
	}
	double x = a;
	ofstream file("output.csv");
	for (int i = 0; i < pol.size(); ++i) {
		file << x << ";" << pol[i] << endl;
		x += 0.05;
	}
	file.close();
	cout << "delta= " << delta << endl;
	return 0;
}