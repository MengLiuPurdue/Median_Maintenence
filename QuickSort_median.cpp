#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <algorithm>

using namespace std;

long result = 0;

int Partition(int *data, int left, int right)
{
//	cout << "left " << left << " right " << right << " : ";	
	int i = left + 1;
	int j = left + 1;
	int temp, pivot;
	int middle = (left + right) / 2;
	if(data[left] < data[right])
	{
		if(data[left] > data[middle])
		{
			pivot = left;
		}
		else
		{
			if(data[right] < data[middle])
			{
				pivot = right;
			}
			else
			{
				pivot = middle;
			}
		}
	}
	else
	{
		if(data[left] < data[middle])
		{
			pivot = left;
		}
		else
		{
			if(data[right] > data[middle])
			{
				pivot = right;
			}
			else
			{
				pivot = middle;
			}
		}
	}
	temp = data[left];
	data[left] = data[pivot];
	data[pivot] = temp;
	while(j <= right)
	{
		if(data[j] < data[left])
		{
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			i ++;
		}
		j ++;
	}
    temp = data[left];
	data[left] = data[i - 1];
	data[i - 1] = temp;

/*	for(int k = left; k <= right; k ++)
	{
		cout << data[k] << " ";
	}
	cout << endl;*/
	return i - 1;
}

void QuickSort(int *data, int left, int right)
{
	if(right <= left)
	{
		return;
	}
	int i = Partition(data, left, right);
	result += right - left;
	QuickSort(data, left, i - 1);
	QuickSort(data, i + 1, right);
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
	int *data = (int *)malloc(sizeof(int) * 10000);
	int i = 0;
//	cout << "here" << endl;
	while(!ss.eof())
	{
		ss >> data[i];
		i ++;
	}
//	cout << i << endl;
	QuickSort(data, 0, i - 2);

	cout << result << endl;
}
