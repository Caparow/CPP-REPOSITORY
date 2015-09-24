/***************************************************************
**************Header file with all methods.*********************
****************************************************************/

#pragma once
#include <iostream>
#include "time.h"
#include <stdio.h>
#include <tchar.h>
#include <math.h>


class chessb
{
public:
	chessb(int N);
	~chessb();
	int N; //Desk size
	void GetRandomState();
	void DrawBoard();
	int Energy(); //Number of conflicts
	void CopySolution(chessb &obj);
private:	
	int* QPos;
};

