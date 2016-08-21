#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <queue>

using namespace std;

class comparator1
{
	public:
		bool operator()(int i, int j)
		{
			return i < j;
		}
};

class comparator2
{
	public:
		bool operator()(int i, int j)
		{
			return i > j;
		}
};

int main(int argc, char *argv[])
{
	FILE *rptr = fopen(argv[1], "r");
	fseek(rptr, 0, SEEK_END);
	long fsize;
	fsize = ftell(rptr);
	char *read_file = (char *)malloc(sizeof(char) * fsize);
	fseek(rptr, 0, SEEK_SET);
	fread(read_file, sizeof(char), fsize, rptr);
	stringstream ss;
	ss << read_file;
	free(read_file);

	priority_queue<int, vector<int>, comparator1> minHeap;
	priority_queue<int, vector<int>, comparator2> maxHeap;

	long median_sum = 0;
	int next, last;
	ss >> next;
	minHeap.push(next);
//	int first, second, next, last;
//	ss >> first;
//	ss >> second;
/*	median_sum = first;
	if(first < second)
	{
		minHeap.push(first);
		maxHeap.push(second);
		median_sum += first;
	}
	else
	{
		minHeap.push(second);
		maxHeap.push(first);
		median_sum += second;
	}
	int count = 2;*/
	while(!ss.eof())
	{
	    cout << "here " << next << " " << maxHeap.size() << endl;
		ss >> next;
		cout << minHeap.top() << " " << median_sum << endl;
		median_sum += minHeap.top();
		if(maxHeap.size() == 0 || next < maxHeap.top())
		{
			minHeap.push(next);
			if(minHeap.size() - maxHeap.size() >= 2)
			{
				last = minHeap.top();
				minHeap.pop();
				maxHeap.push(last);
			}
		}
		else
		{
			maxHeap.push(next);
			if(maxHeap.size() - minHeap.size() >= 1)
			{
				last = maxHeap.top();
				maxHeap.pop();
				minHeap.push(last);
			}
		}
	}

	int mod;
	mod = median_sum % 10000;
	cout << mod << endl;
}
