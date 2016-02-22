#include "header.h"

int main()
{
	srand(time(NULL));
	int graph_size;
	string filename;
	vector<edge> graph;
	int temp_rand;
	int temp_edge;
	int iter = 0;

	int ants = 10;
	int Pn = 0.95;
	int Pc = 0.5;

	filename = "yuzGCPrnd83.9.col";
	int colors = 9;

	if (ReadFromFile(graph, graph_size, filename))
	{
		cout << "Filename: " << filename << endl;
		cout << "Number of edges: " << graph_size << endl;

		for (int i = 0; i < graph_size; ++i)
			graph[i].confl = Local_confl_num(graph, graph_size, i);

		for (int k = 0; k < 10; ++k)
		{
			for (int j = 0; j < ants; ++j)
			{
				for (int i = 1; i < graph_size; ++i)
				{
					temp_rand = ((double)rand() / (RAND_MAX + 1));
					if (temp_rand <= Pn)
					{
						temp_edge = Worst_neighbour_edge(graph, graph_size, i);
						Get_new_color(graph, graph_size, temp_edge, colors);
					}
					else
					{
						temp_rand = ((double)rand() / (RAND_MAX + 1));
						if (temp_rand <= Pc)
						{
							temp_edge = rand() % graph_size;
							Get_new_color(graph, graph_size, temp_edge, colors);
						}
					}
					Pn *= 0.99;			
					cout << "New Global conflicts: " << Global_confl_num(graph, graph_size) << endl;
				}
				cout << "New chromatic number: " << Chromatic_number(graph, graph_size) << endl;
			}
		}
		
		cout << "New chromatic number: " << Chromatic_number(graph, graph_size) << endl;
		return 0;
	}
	else
	{
		cout << "File not found, sry :c" << endl;
		return 0;
	}
}