#include <iostream>
#include "vars.h"
#include "Gauss_Gordan_mehod.h"

using namespace std;

void printmatr() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
}

void Gauss_Gordan_method() {
	for (int m = 0; m < N; m++) {

		for (int j = m + 1; j <= N; j++) {
			a[m][j] /= a[m][m];
		}a[m][m] = 1;

		for (int i = 0; i < N; i++) {
			for (int j = m + 1; j <= N; j++) {
				if (i != m) {
					a[i][j] -= a[m][j] * a[i][m];
				}
				else { break; }
			} if (i != m) { a[i][m] = 0; }
		}

	}
	printmatr();
}