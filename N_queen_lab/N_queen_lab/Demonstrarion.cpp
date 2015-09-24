/***********************************************************
*****************Demonstration of solution.*****************
***********************************************************/

#include "chessb.h"

int main()
{
	srand(time(NULL));

	const double MinT = 0.000001;          //Minimal temperature for algorithm.
	const double Alpha = 0.98;             //Coefficient for temperarure function. (T=t*Alpha)
	const int Iterations = 100;
	double Temperature = 30;

	int DSize;
	int workConflicts, resConflicts;
	float delta, calc;
	double TempStep, test;

	std::cout << "Enter size of your desk: ";
	std::cin >> DSize;
	
	chessb res(DSize);                      //Resault board.
	chessb working(DSize);                  //"Working" board, that was changed.

	while (Temperature > MinT)
	{
		for (int i = 0; i < Iterations; ++i)
		{
        	working.CopySolution(res);
        	working.GetRandomState();

	        workConflicts = working.Energy();
	        resConflicts = res.Energy();

        	if (resConflicts > workConflicts)
	        	res.CopySolution(working);
	        else
	        {
	        	test = (double)rand() / (RAND_MAX + 1);
	        	delta = resConflicts - workConflicts;
		        calc = exp(delta / Temperature);
	        	if (calc >= test)
		         	res.CopySolution(working);
	        }

			if (res.Energy() == 0)
				break;
        }
		Temperature *= Alpha;
	}
	
	res.DrawBoard();
	std::cout << "Number of conflicts: " << res.Energy()<< "\n";

	system("PAUSE");

	return 0;
}