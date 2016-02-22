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

		graph.resize(graph_size+1);

		while (!f.eof())
		{
			buf = ' ';
			f >> buf;
			if (buf == 'e')
			{
				f >> temp_edge;
				f >> temp_neighbour;
				graph[temp_edge].neighbours.insert(temp_neighbour);
				graph[temp_neighbour].neighbours.insert(temp_edge);
			}
		}
		return true;
	}
	else
		return false;
}

int Global_confl_num(vector<edge> graph, int graph_size)
{
	int buf_confl_num = 0;

	for (int i = 1; i < graph_size - 1; ++i)
		buf_confl_num += Local_confl_num(graph, graph_size, i);

	return buf_confl_num;
}

int Local_confl_num(vector<edge> graph, int graph_size, int i)
{
	int buf_confl_num = 0;

	for (auto& j = graph[i].neighbours.begin(); j != graph[i].neighbours.end(); j++)
		if (graph[i].color == graph[*j].color)
			++buf_confl_num;
	
	return buf_confl_num;
}

int Worst_neighbour_edge(vector<edge> graph, int graph_size, int i)
{
	int max_confl = 0;
	int max_edge = 0;
	int buf_confl;

	for (auto& j = graph[i].neighbours.begin(); j != graph[i].neighbours.end(); j++)
	{
		buf_confl = graph[*j].confl;
		if (max_confl < buf_confl)
		{
			max_confl = buf_confl;
			max_edge = *j;
		}
	}
	
	return max_edge;
}

void Get_new_color(vector<edge>& graph, int graph_size, int i, int& colors)
{
	int buf_color = graph[i].color;
	int buf_confl = Local_confl_num(graph, graph_size, i);
	int alt_color = graph_size-1;
	int talt_conf = buf_confl;
	int alt_confl = graph_size - 1;
	bool flag = false;

	cout << "color " << i << " " << graph[i].color << endl;
	for (int j = 0; j < colors; ++j)
	{
		graph[i].color = j;
		int loc_buf = Local_confl_num(graph, graph_size, i);
		if (loc_buf < buf_confl)
		{
			buf_color = j;
			buf_confl = loc_buf;
			flag = true;
			if (loc_buf == 0)
				break;
		}
		else
			if ((loc_buf < alt_confl) && (loc_buf > talt_conf))
			{
				alt_color = j;
				alt_confl = loc_buf;
			}
	}

	if (flag = true)
		graph[i].color = buf_color;
	else
		graph[i].color = alt_color;

	cout << "color " << i << " " << graph[i].color << endl;
	graph[i].confl = Local_confl_num(graph, graph_size, i);
}

int Chromatic_number(vector<edge> graph, int graph_size)
{
	set<int> colors;

	for (int i = 0; i < graph_size; ++i)
		colors.insert(graph[i].color);
	
	return colors.size();
}