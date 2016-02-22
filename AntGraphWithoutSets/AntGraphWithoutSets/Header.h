#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include <set>

using namespace std;

struct edge
{
	int color = 0;
	int confl;
	vector<edge*> neighbours;
};

bool ReadFromFile(vector<edge>&, int&, string);
int Global_confl_num(vector<edge>);
int Local_confl_num(edge);
int Worst_neighbour_edge(edge);
void Get_new_color(edge*&, int);
int Chromatic_number(vector<edge>);