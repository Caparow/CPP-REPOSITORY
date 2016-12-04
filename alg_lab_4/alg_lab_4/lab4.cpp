#include <stdio.h>
#include <math.h>

const double A = 1.0; 
const double B = 17.0;
const double EPS = 0.0001; 
const int r = 4;

double f(double);
double f_4(double);
double F(double);
double integral(double);

int main() {
	int n; 
	double Rn, h; 
	double I0, In, I2n; 
	double x, delta, M4;
	
	I0 = F(B) - F(A);
	
	printf("EPS\t\th\t\tValue\t\tError\n");
	
	x = A;
	M4 = fabs(f_4(x));
	while (x<B) {
		if (fabs(f_4(x)) > M4)
			M4 = fabs(f_4(x));
		x += EPS;
	}

	h = pow(180.0*EPS/((B - A)*M4), 0.25);
	n = 2*ceil(0.5*(B - A)/h);
	h = (B - A)/n;
	delta = fabs(I0 - integral(n));
	printf("%.10f\t%.10f\t%.10f\t%.10f\n\n", EPS, h, integral(n), delta);
	
	printf("Error\t\th\t\tAbs.Error\n");
	n = ceil(1/pow(EPS, 1.0/r));
	In = integral(n);
	I2n = integral(2*n);
	
	Rn = fabs(In - I2n)/(pow(2.0,r) - 1);
	while (Rn > delta) {
		n *= 2;
		In = integral(n);
		I2n = integral(2*n);
		Rn = fabs(In - I2n)/15;
	}
	
	printf("%.10f\t%.10f\t\%.10f\n", delta, 0.5*(B - A)/n, fabs(I0 - I2n));
}

double f(double x) {
	return sqrt(3*x+2);
}

double f_4(double x) {
	return -1215/(sqrt(3*x+2)*(432*x*x*x+864*x*x+576*x+128));
}

double F(double x) {
	return 2*pow(sqrt(3*x+2),3)/9;
}

double integral(double n) {
	double h; 
	double s1 = 0.0, 
		   s2 = 0.0; 

	n = 2*ceil(n/2);
	h = (B - A)/n;
	for (int i = 1; i < n; i++) {
		if (i%2 == 0)
			s2 += f(A + i*h);
		else
			s1 += f(A + i*h);
	}
 	
	return h/3*(f(A) + f(B) + 4*s1 + 2*s2);
}