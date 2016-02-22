#include "header.h"

using namespace std;


int main()
{
	srand(time(NULL));

restart:

	int graph_size;
	string filename;
	vector<edge> graph;			    

	
	int iter = 0;                 
	int restart_point = 1000;          //number for iterations with same global conflicts before restart
	int check_point = 0;
	
	
	filename = "yuzGCPrnd157.10.col";   //filename
	// а) легкие:  yuzGCP130.13.col, yuzGCP660.33.col и  yuzGCP990.33.col;
	// b) средние:  yuzGCPrnd83.10.col, yuzGCPrnd127.14.col и  yuzGCPrnd157.10.col;
	// с) трудные:  yuzGCPrnd83.9.col, yuzGCPrnd127.13.col и  yuzGCPrnd157.9.col.

	int colors_num = 9;             //change chromatic number (one less than in file)
	

	if (ReadFromFile(graph, graph_size, filename))
	{
		int ants_numb = 3;           //atns number
		vector<edge*> ants(ants_numb); // ants vector


		cout << "Filename: " << filename << endl;
		cout << "Number of edges: " << graph_size << "\n\n";

		for (int i = 0; i < graph.size(); ++i)
		{
			graph[i].confl = Local_confl_num(graph[i]);
			graph[i].color = 0;
		}
			

		for (int i = 0; i < ants_numb; ++i)
			ants[i] = &graph[rand() % graph_size];

		int glob = Global_confl_num(graph);
		int old_glob = glob;

		while (glob > 0)
		{
			for (int i = 0; i < ants_numb; ++i)
			{

				if (Local_confl_num(*ants[i]) != 0) //skip edge without conflicts
				{
					glob -= Local_confl_num(*ants[i]);

					Get_new_color(ants[i], colors_num);  //change color

					glob += Local_confl_num(*ants[i]);   //change global conf.num.

					for (auto& edge : ants[i]->neighbours)
						edge->confl = Local_confl_num(*edge);
					ants[i]->confl = Local_confl_num(*ants[i]);
				}
				
				if ((double)rand() / (RAND_MAX + 1) <= exp(-1 /(glob + 1)) / iter) //go to the next edge
					ants[i] = &graph[Worst_neighbour_edge(*ants[i])];
				else
					ants[i] = ants[i]->neighbours[rand() % ants[i]->neighbours.size()];
			}
			++iter;
			//cout << "Iter: " << iter << "      Conflicts: " << glob << endl;
			if (old_glob == glob) // check for restart
			{
				++check_point;
				if (check_point > restart_point)
				{
					cout << "\n\n\n\n\n\n\n\n";
					cout << "Need to restart algorithm to exit loop. \n\n" ;
					goto restart;					
				}
			}
			else
			{
				old_glob = glob;
				check_point = 0;
			}
		}
	
		cout << "New chromatic number: " << Chromatic_number(graph) << " At iter:" << iter << endl;
		cout << "Colors of edges: \n";
		for (int i = 0; i < graph_size; ++i)
			printf("%d ", graph[i].color);
		return 0;
	}
	else
	{
		cout << "File not found, sry :c" << endl;
		return 0;
	}
}