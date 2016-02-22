#include "knapsack.h"

using namespace std;

knapsack::knapsack()
{

	ifstream fin("knapsack128.in");

	fin >> N;
	fin >> b_weight;

	knapsackItems = new item[N];

	for (int i = 0; i < N; ++i)
		fin >> knapsackItems[i].price; 

	for (int i = 0; i < N; ++i)
		fin >> knapsackItems[i].weight;
	
	fin.close();	

	for (int s = 0; s < N; ++s)
	{
		int ind, i;
		item max;

		max = knapsackItems[s];
		ind = s;

		for (i = s + 1; i < N; ++i)
			if (knapsackItems[i].price > max.price)
			{
				max = knapsackItems[i];
				ind = i;
			}

		knapsackItems[ind] = knapsackItems[s];
		knapsackItems[s] = max;
	}

	
	for (int i = 0; i < N*3; ++i)
	{
		int temp = rand() % N;
		if (knapsackItems[temp].weight + Weight() <= b_weight)
			knapsackItems[temp].isHere = true;

		if (Weight() == b_weight)
			break;
	}

}


knapsack::~knapsack()
{
	if (knapsackItems != NULL)
		delete[] knapsackItems;
}


void knapsack::InOutItem()
{
	int t = rand() % 2 + 1;

	for (int i = 0; i < t; ++i)
	{
		int temp1 = rand() % N;

		while (knapsackItems[temp1].isHere != true)
			temp1 = rand() % N;
		knapsackItems[temp1].isHere = false;
	}

	for (int i = rand() % N; i < N; ++i)
	{
		if (knapsackItems[i].weight + Weight() <= b_weight)
			knapsackItems[i].isHere = true;

		if (Weight() == b_weight)
			break;
	}
}


void knapsack::CopyState(const knapsack &obj)
{
	for (int i = 0; i < N; ++i)
	    this->knapsackItems[i].isHere = obj.knapsackItems[i].isHere;
}


double knapsack::Price()
{
	double t_price = 0;
	for (int i = 0; i < N; ++i)
		if (knapsackItems[i].isHere == true)
			t_price += knapsackItems[i].price;

	return t_price;
}

  
double knapsack::Weight()
{
	double t_weight = 0;
	for (int i = 0; i < N; ++i)
		if (knapsackItems[i].isHere == true)
			t_weight += knapsackItems[i].weight;

	return t_weight;
}


void knapsack::KnapsackOut()
{
	cout << "There is our solution for your problem: \n\n";
	cout << "Resault Weight: " << Weight() << "kg Resault Price: " << Price() << "$\n";
}