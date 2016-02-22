#include "header.h"

using namespace std;


bool ReadFromFile(vector<edge>& graph, int& graph_size, string filename)
{
	char buf;
	int conn_num;
	int temp_edge, temp_neighbour;
	string buf_line = "";

	ifstream f(filename);
	if (f.is_open())
	{
		f >> buf;

		while (buf == 'c')
		{
			getline(f, buf_line, '\n');
			buf = ' ';
			f >> buf;
		}

		if (buf == 'p')
		{
			f >> buf_line;
			f >> graph_size;
			f >> conn_num;
		}

		graph.resize(graph_size);

		while (!f.eof())
		{
			buf = ' ';
			f >> buf;
			if (buf == 'e')
			{
				f >> temp_edge;
				f >> temp_neighbour;
				graph[temp_edge-1].neighbours.push_back(&graph[temp_neighbour-1]);
				graph[temp_neighbour - 1].neighbours.push_back(&graph[temp_edge - 1]);
			}
		}
		return true;
	}
	else
		return false;
}

int Global_confl_num(vector<edge> graph)
{
	int buf_confl_num = 0;

	for (int i = 0; i < graph.size(); ++i)
		buf_confl_num += Local_confl_num(graph[i]);

	return buf_confl_num/2;
}

int Local_confl_num(edge graph)
{
	int buf_confl_num = 0;
	int tmp_edge_color = graph.color;

	for (int j = 0; j < graph.neighbours.size(); ++j)
		if (tmp_edge_color == (*graph.neighbours[j]).color)
			++buf_confl_num;
	
	return buf_confl_num;
}

int Worst_neighbour_edge(edge graph)
{
	int max_confl = 0;
	int max_edge = 0;
	int buf_confl;

	for (int j = 0; j < graph.neighbours.size(); ++j)
	{
		buf_confl = (*(graph.neighbours[j])).confl;
		if (max_confl < buf_confl)
		{
			max_confl = buf_confl;
			max_edge = j;
		}
	}
	
	return max_edge;
}



void Get_new_color(edge*& graph, int chrom_num)
{
	int cur_color = graph->color;
	int max_conf = graph->neighbours.size();
	int new_color;

	for (int j = 0; j <= chrom_num; ++j)
	{
		if (j == cur_color)
			continue;

		graph->color = j;
		int new_conf = Local_confl_num(*graph);
		if (new_conf < max_conf)
		{
			new_color = j;
			max_conf = new_conf;
		}
	}

	graph->color = new_color;
}

int Chromatic_number(vector<edge> graph)
{
	set<int> colors_set;

	for (int i = 0; i < graph.size(); ++i)
		colors_set.insert(graph[i].color);
	
	return colors_set.size();
}