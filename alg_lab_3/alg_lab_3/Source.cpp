#include <iostream>
#include "Gauss_Gordan_mehod.h"
#include "Gauss_Seidel_method.h"

using namespace std;

int main() {

	cout << "\t\tGauss-Seidel method:\n";
	Gauss_Seidel_method();
	cout << "\n";

	cout << "\t\tGauss-Gordan method:\n";
	Gauss_Gordan_method();

	system("PAUSE");
	return 0;
}