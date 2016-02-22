#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include <set>

using namespace std;

struct edge
{
	set<int> neighbours;
	int color = 0;
	int confl;
};

bool ReadFromFile(vector<edge>&, int&, string);
int Global_confl_num(vector<edge>, int);
int Local_confl_num(vector<edge>, int, int);
int Worst_neighbour_edge(vector<edge>, int, int);
void Get_new_color(vector<edge>&, int, int, int&);
int Chromatic_number(vector<edge>, int);