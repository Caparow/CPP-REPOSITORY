#include <iostream>
#include <math.h>
#include "Gauss_Seidel_method.h"
#include "vars1.h"

using namespace std;

void printmatr1() {
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N1; j++) {
			cout << a1[i][j] << " ";
		}
		cout << x[i];
		cout << "\n";
	}
}

void Gauss_Seidel_method() {
	int i, j;
	double norma; //Чебышевская норма вектора
	double xn[N1] = { 0 };//вектор для текущей итерации, начальное значение
						  //должно быть равно начальному приближению

	do {

		norma = 0.0;
		for (i = 0; i < N1; i++) {
			x[i] = -b[i];
			for (j = 0; j < N1; j++) {
				if (i != j)
					x[i] += a1[i][j] * x[j];
			}
			x[i] /= -a1[i][i];
		}

		for (i = 0; i < N1; i++) {
			if (fabs(x[i] - xn[i]) > norma)
				norma = fabs(x[i] - xn[i]); //Вычисление нормы вектора
			xn[i] = x[i];
		}
	} while (norma > eps); //проверка на необходимую точность вычислений

						   //printmatr1();
	for (int i = 0; i < N1; i++) {
		cout << "x[" << i << "]=" << x[i] << " \n";
	}
}