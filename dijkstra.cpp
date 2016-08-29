#include <iostream>
#include <queue>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <climits>
#include <algorithm>
#include <fstream>
#include <string.h>

using namespace std;

#define nodeNum 11

class NodeMinKey{
	public:
	int node;
	int MinKey = INT_MAX;
};

class Edge{
	public:
	int v;
	int num;
	int cap;
};

class comparator{
	public:
	bool operator()(NodeMinKey i, NodeMinKey j){
		return i.MinKey > j.MinKey;
	}
};

int main(int argc, char *argv[])
{
	ifstream rptr;
	rptr.open(argv[1], ifstream::in);
	string newline;
	stringstream ss;
	const char *split = ",";
	char *p;
	char *line;
	NodeMinKey key[nodeNum + 1];
	int id1;
	int id2;
	int cap;
	vector<Edge> edges[nodeNum + 1];
	int A[nodeNum + 1];
	while(getline(rptr, newline))
	{
		cout << newline << endl;
		line = (char *)newline.data();
		p = strtok(line, split);
		while(p != NULL)
		{
			ss << p;
			ss << " ";
			p = strtok(NULL, split);
		}
		ss >> id1;
		while(!ss.eof())
		{
			ss >> id2;
			ss >> cap;
			Edge s = {id2, (int)edges[id2].size(), cap};
			Edge d = {id1, (int)edges[id1].size(), cap};
			edges[id1].push_back(s);
			edges[id2].push_back(d);
		}
		ss.clear();
	}

	priority_queue<NodeMinKey, vector<NodeMinKey>, comparator> minHeap;
	int i, j;
	vector<int> X, V_X;
	int count = 1;
	X.push_back(count);
	count ++;
	while(count <= nodeNum)
	{
		V_X.push_back(count);
		count ++;
	}
	for(i = 0; i < (int)V_X.size(); i ++)
	{
		key[V_X[i]].node = V_X[i];
		for(j = 0; j < (int)edges[V_X[i]].size(); j ++)
		{
			int to = edges[V_X[i]][j].v;
			if(find(X.begin(), X.end(), to) != X.end())
			{
				if(edges[V_X[i]][j].cap < key[V_X[i]].MinKey)
				{
					key[V_X[i]].MinKey = edges[V_X[i]][j].cap;
				}
			}
		}
		minHeap.push(key[V_X[i]]);
	}
	A[1] = 0;
	while(!V_X.empty())
	{
		NodeMinKey min_key;
	    min_key = minHeap.top();
		minHeap.pop();
		int v = min_key.node;
		A[v] = min_key.MinKey;
		cout << v << endl;
//		int *p = find(V_X.begin(), V_X.end(), v);
		for(i = 0; i < (int)edges[v].size(); i ++)
		{
			int w = edges[v][i].v;
			if(find(V_X.begin(), V_X.end(), w) != V_X.end())
			{
				if(A[v] + edges[v][i].cap < key[w].MinKey)
				{
					key[w].MinKey = edges[v][i].cap + A[v];
				}
			}
		}
	    X.push_back(v);
	    V_X.erase(find(V_X.begin(), V_X.end(), v));
		minHeap = priority_queue<NodeMinKey, vector<NodeMinKey>, comparator>();
		for(i = 0; i < (int)V_X.size(); i ++)
		{
			minHeap.push(key[V_X[i]]);
		}
	}


/*	for(i = 0; i < 3; i ++)
	{
		NodeMinKey a;
		a = minHeap.top();
		minHeap.pop();
		cout << a.node << " " << a.MinKey << endl;
	}*/

	for(i = 1; i < nodeNum + 1; i ++)
	{
		cout << i << " " << A[i] << endl;
	}
}
