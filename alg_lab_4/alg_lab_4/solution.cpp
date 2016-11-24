#include <iostream>
#include <stdio.h>  
#include <math.h>

const int A = 1;
const int B = 0;
const float M4 = 1;
const float EPS = 0.001;
const int N = 4;

const int R = 4;
const int N1 = ceil(1 / pow(EPS, 1 / R));

float integral(float, float, float, int, bool);
float f(float);
float f1(float);
int n();
void RefinedCalc(int, float);

int main()
{
	float result;

	printf("EPS\t\th\t\tValue\t\tError\n");
	result = integral(A, B, EPS, N, 1);
	printf("\n");
	RefinedCalc(N1, fabs(result - (f1(A) - f1(B))));

	return 0;
}


int n() {
	printf("%f ", pow((pow(B - A, 5.0)*M4 / (180 * EPS)), 1 / 4));
	return ceil(pow((pow(B - A, 5.0)*M4 / (180 * EPS)), 1 / 4));
}

float f1(float x){
	return 2 * pow(sqrt(3 * x + 2), 3) / 9;
}

float f(float x){
	return sqrt(3 * x + 2);
}

void RefinedCalc(int N1, float e)
{
	int n;
	int n_2;
	int res1, res2;
	float Rn;

	do {
		n = N1;
		n_2 = 2 * n;

		res1 = integral(A, B, e, n, 0);
		res2 = integral(A, B, e, n_2, 1);
		Rn = res1 - res2;
	} while (fabs(Rn) >= e);
}


float integral(float a, float b, float e, int N, bool on)
{
	int n = N, i;
	float s_ab = f(a) + f(b);
	float h = (b - a) / n;
	float s_even = 0, s_odd;
	float s_res = 0, s_pres;

	if (on == 1) {
		printf("%f\t", e);
		printf("%f\t", fabs(h));
		printf("%f\t", fabs(f1(a) - f1(b)));
	}


	for (i = 2; i < n; i += 2) {
		s_even += f(a + i * h);
	}
	do {
		s_odd = 0;
		s_pres = s_res;


		for (i = 1; i < n; i += 2) {
			s_odd += f(a + i * h);
		}

		s_res = h / 3 * (s_ab + 2 * s_even + 4 * s_odd);

		if (s_res == 0) s_res = e;

		s_even += s_odd;
		n *= 2;
		h /= 2;
	} while (fabs((s_pres - s_res) / s_res) > e);

	if (on == 1) { printf("%f\t\n", fabs(fabs(s_res) - (f1(a) - f1(b)))); }
	return fabs(s_res);
}
