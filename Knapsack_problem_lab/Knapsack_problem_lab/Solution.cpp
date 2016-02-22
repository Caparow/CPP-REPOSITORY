#include "knapsack.h"

int main()
{
	srand(time(NULL));

	const double alpha = 0.98;
	const double minTemp = 1E-50;
	const int iterations = 50;
	double temperature = 30;

	double workPrice;
	double resPrice;
	double workWeight;
	double resWeight;

	knapsack working;
	knapsack res;

	while (temperature > minTemp)
	{
		for (int i = 0; i < iterations; ++i)
		{
			working.CopyState(res);
			working.InOutItem();

			workPrice = working.Price();
			resPrice = res.Price();

			if (workPrice > resPrice)
				res.CopyState(working);
			else
			{
				double test = (double)rand() / (RAND_MAX + 1);
				double delta = workPrice - resPrice;
				double calc = exp(delta / temperature);
				if (calc >= test)
					res.CopyState(working);
			}
		}
		temperature *= alpha;
	}

	res.KnapsackOut();

	system("PAUSE");
	return 0;
}