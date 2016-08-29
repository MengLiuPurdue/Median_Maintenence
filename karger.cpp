#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <limits.h>

using namespace std;

typedef struct _Edge
{
	int src, dest;
}Edge;

typedef struct _Graph
{
	int V, E;
	Edge* edge;
}Graph;

Graph* createGraph(int V, int E)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->edge = (Edge*)malloc(sizeof(Edge) * E);

	return graph;
}

typedef struct _subset
{
	int parent;
	int rank;
}subset;

int find(subset* subsets, int i)
{
	if(subsets[i].parent != i)
	{
		subsets[i].parent = find(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

void Union(subset* subsets, int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if(subsets[xroot].rank < subsets[yroot].rank)
	{
		subsets[xroot].parent = yroot;
	}
	else if(subsets[xroot].rank > subsets[yroot].rank)
	{
		subsets[yroot].parent = xroot;
	}
	else
	{
		subsets[xroot].parent = yroot;
		subsets[yroot].rank ++;
	}
}

int karger(Graph* graph)
{
	int E = graph->E;
	int num = graph->V;
	subset* subsets = (subset*)malloc(sizeof(subset) * (graph->V + 1));
	for(int j = 1; j < graph->V + 1; j ++)
	{
		subsets[j].parent = j;
		subsets[j].rank = 0;
	}

	while(num > 2)
	{
		int i = rand() % E;
		int src = graph->edge[i].src;
		int dest = graph->edge[i].dest;
		if(find(subsets, src) != find(subsets, dest))
		{
	//		cout << src << "->" << dest << endl;
			Union(subsets, src, dest);
			num --;
		}
	}

	int result = 0;
	for(int j = 0; j < E; j ++)
	{
		int src = graph->edge[j].src;
		int dest = graph->edge[j].dest;
		if(find(subsets, src) != find(subsets, dest))
		{
			result ++;
		}
	}

	return result / 2;
}

int main(int argc, char *argv[])
{
	ifstream rptr;
	rptr.open(argv[1], ifstream::in);
/*	fseek(rptr, 0, SEEK_END);
	int fsize;
	fsize = ftell(rptr);
	char *read_file = (char *)malloc(sizeof(char) * fsize);
	fseek(rptr, 0, SEEK_SET);
    fread(read_file, sizeof(char), fsize, rptr);
	stringstream ss;
	ss << read_file;
	free(read_file);*/

//	cout << "here" << endl;
	int V = atoi(argv[2]);
//	cout << V << endl;
	int max_E = V * (V - 1);
	int E;
	int src, dest;
	Graph* graph = createGraph(V, max_E);
	string newline;
	stringstream ss;
	int i = 0;
	while(getline(rptr, newline))
	{
		ss << newline;
		cout << newline << endl;
		ss >> src;
		while(!ss.eof())
		{
	//		cout << "i =" << i << endl;
			ss >> dest;
			graph->edge[i].src = src;
			graph->edge[i].dest = dest;
			i ++;
		}
		ss.clear();
	}
	E = i;
	graph->E = E;
/*	for(i = 0; i < E; i ++)
	{
		cout << graph->edge[i].src << " " << graph->edge[i].dest << endl;
	}*/
	int result = INT_MAX;
	//cout << V * V * 5 << endl;
	srand((unsigned int)time(NULL));
	for(i = 0; i < V * V * 5; i ++)
//	for(i = 0; i < 1000000; i ++)
	{
		cout << i << endl;
		int temp = karger(graph);
		cout << "temp = " << temp << endl;
		if(temp < result)
		{
			result = temp;
		}
	}

	cout << result << endl;
}
