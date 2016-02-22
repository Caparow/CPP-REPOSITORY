#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "time.h"
#include <cstdio>


struct item
{
	double weight, price;
	bool isHere = false;
};


class knapsack
{
public:
	knapsack();
	~knapsack();
	double b_weight = 0;
	int N = 0;
	double Price();
	double Weight();
	void InOutItem();
	void CopyState(const knapsack &obj);
	void KnapsackOut();
private:
	item* knapsackItems;
};

