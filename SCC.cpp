#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

#define nverts 875714

vector<int> *G;
vector<int> *Grev;
int *label;
int *leader;

int t = 0;
int s;
int SCC_size;

class NodeFinish
{
	public:
		int node;
		int f;
};

class comparator
{
	public:
		bool operator()(NodeFinish i, NodeFinish j)
		{
			return i.f < j.f;
		}
};

class comparator1
{
	public:
		bool operator()(int i, int j)
		{
			return i < j;
		}
};

priority_queue<NodeFinish, vector<NodeFinish>, comparator> maxHeap;
priority_queue<int, vector<int>, comparator1> sizeHeap;

void DFS_rev(int i)
{
	label[i] = 0;
	leader[i] = s;
//	cout << "ok" << endl;
	int j, dest;
	for(j = 0; j < (int)Grev[i].size(); j ++)
	{
		dest = Grev[i][j];
		if(label[dest] == -1)
		{
			DFS_rev(dest);
		}
	}

	t ++;
	NodeFinish new_node = {i, t};
	maxHeap.push(new_node);
}

void DFS(int i)
{
	SCC_size ++;
	label[i] = 0;
	int j, dest;
	for(j = 0; j < (int)G[i].size(); j ++)
	{
		dest = G[i][j];
		if(label[dest] == -1)
		{
			DFS(dest);
		}
	}
}

int main(int argc, char *argv[])
{
    FILE *rptr = fopen(argv[1], "r");
	fseek(rptr, 0, SEEK_END);
	int fsize;
	fsize = ftell(rptr);
	char *read_file = (char *)malloc(sizeof(char) * fsize);
	fseek(rptr, 0, SEEK_SET);
    fread(read_file, sizeof(char), fsize, rptr);
	stringstream ss;
	ss << read_file;
	free(read_file);

	int src, dest, i;
	cout << "here" << endl;
	G = (vector<int> *)malloc(sizeof(vector<int>) * (nverts + 1));
	Grev = (vector<int> *)malloc(sizeof(vector<int>) * (nverts + 1));
	while(!ss.eof())
	{
		ss >> src;
		ss >> dest;
		G[src].push_back(dest);
		Grev[dest].push_back(src);
	}

	label = (int *)malloc(sizeof(int) * (nverts + 1));
	leader = (int *)malloc(sizeof(int) * (nverts + 1));

	fill(label, label + nverts + 1, -1);

	cout << "here" << endl;

	for(i = nverts; i > 0; i --)
	{
	//	cout << i << endl;
		if(label[i] == -1)
		{
			s = i;
			DFS_rev(i);
		}
	}

	cout << "here" << endl;
	i = nverts;
	int count = 0;
	fill(label, label + nverts + 1, -1);
	while(i > 0)
	{
		SCC_size = 0;
		NodeFinish next_node = maxHeap.top();
		maxHeap.pop();
		if(label[next_node.node] == -1)
		{
			count ++;
			DFS(next_node.node);
		}
		sizeHeap.push(SCC_size);
		i --;
	}
	cout << "here" << endl;

	if(count < 5)
	{
		for(i = 0; i < count; i ++)
		{
			cout << sizeHeap.top() << endl;
			sizeHeap.pop();
		}
	}
	else
	{
		for(i = 0; i < 5; i ++)
		{
			cout << sizeHeap.top() << endl;
			sizeHeap.pop();
		}
	}

	free(G);
	free(Grev);
	free(label);
	free(leader);
}
