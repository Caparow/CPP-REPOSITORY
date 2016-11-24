#pragma once 
#include "functions.h"

int getM(long double x) {
	int temp = 0;
	while (x > 2) {
		x = x / 2;
		temp++;
	}
	return (temp+1);
}

long double calcR(int n) {
	long double temp;
	temp = (1.0 / (4 * (2 * n + 1)))*(pow((1.0 / 3.0), (2 * n - 1)));
	return temp;
}

long double calcL(long double x, int k) {
	long double temp = 0;
	long double z = 0;
	long double a = 0;
	int m = 0;

	m = getM(x);
	z = x / pow(2, m);
	a = (1 - z) / (1 + z);

	temp = pow(a, (2*k-1))/(2*k-1);

	return (temp);
}