/******************************************************
***************.cpp file with methodsr.****************
*******************************************************/

#include "chessb.h"

chessb::chessb(int size)
{
	N = size;
	QPos = new int[N];

	for (int i = 0; i < N; ++i)
		QPos[i] = i;

	for (int i = 0; i < 60; ++i)
		GetRandomState();
}


chessb::~chessb()
{
	if (QPos != nullptr)
		delete[] QPos;
}

//Generate random state of board
void chessb::GetRandomState()
{
	int BoofIn1, BoofIn2, BoofVal;

	BoofIn1 = rand() % N;  
	BoofIn2 = rand() % N;

	while (BoofIn1==BoofIn2)
		BoofIn2 = rand() % N;

	BoofVal = QPos[BoofIn1];
	QPos[BoofIn1] = QPos[BoofIn2];
	QPos[BoofIn2] = BoofVal;
	
}

//Drow chess board with queens
void chessb::DrawBoard()
{
	std::cout << "\nHere your solution: \n\n";

	int size;
	if (N >= 39)
		size = 39;
	else
		size = N;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			if (j == QPos[i])
				std::cout << char(5) << " ";
			else
				std::cout << "=" << " ";
		std::cout << "\n";
	}

	if (size == 39)
		std::cout << "\nSorry, but your board is too big. I can draw only 39x39 board :( \n\n";
}

//Find number of conflicts on the board
int chessb::Energy()
{
	int ConflictNumb = 0;
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 1; j < N-i; ++j)
		{
			if (QPos[i+j] == QPos[i] - j)
				++ConflictNumb;
			if (QPos[i+j] == QPos[i] + j)
				++ConflictNumb;
		}
	}
	return ConflictNumb;
}

//Copy board to the main state
void chessb::CopySolution(chessb &obj)
{
	for (int i = 0; i < N; ++i)
		this->QPos[i] = obj.QPos[i];
}
