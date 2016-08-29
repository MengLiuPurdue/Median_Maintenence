#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

long Merge_CountSplitInv(int *data, int low, int mid, int high);
long Sort_Count(int *data, int low, int high)
{
	if(low >= high)
	{
		return 0;
	}
	else
	{
		int mid = (low + high) / 2;
		long X = Sort_Count(data, low, mid);
		long Y = Sort_Count(data, mid + 1, high);
		long Z =	Merge_CountSplitInv(data, low, mid, high);
		return X + Y + Z;
	}
}

long Merge_CountSplitInv(int *data, int low, int mid, int high)
{
	int *c = (int *)malloc(sizeof(int) * 200000);
	int i, j, k;
	i = low;
	j = mid + 1;
	k = low;
	long result = 0;
	while(i <= mid && j <= high)
	{
		if(data[i] < data[j])
		{
			c[k] = data[i];
			i ++;
			k ++;
		}
		else
		{
			c[k] = data[j];
		//	for(int m = i; m <= mid; m ++)
		//	{
		//		cout << data[j] << " " << data[m] << endl;
		//	}
			j ++;
			k ++;
//			cout << mid - i + 1 << endl;
			result += mid - i + 1;
		}
	}
	while(i <= mid)
	{
		c[k] = data[i];
		i ++;
		k ++;
	}
	while(j <= high)
	{
		c[k] = data[j];
		j ++;
		k ++;
	}
	for(i = low; i <= high; i ++)
	{
		data[i] = c[i];
	}
	free(c);

	return result;
}

int main(int argc, char *argv[])
{
	FILE *rptr = fopen(argv[1], "r");
//	cout << "here" << endl;
	fseek(rptr, 0, SEEK_END);
//	cout << "here" << endl;
	int fsize;
	fsize = ftell(rptr);
	char *read_file = (char *)malloc(sizeof(char) * fsize);
	fseek(rptr, 0, SEEK_SET);
	fread(read_file, sizeof(char), fsize, rptr);
	stringstream ss;
	ss << read_file;
	free(read_file);
	int *data = (int *)malloc(sizeof(int) * 200000);
	int i = 0;
//	cout << "here" << endl;
	while(!ss.eof())
	{
		ss >> data[i];
		i ++;
	}
//	cout << i << endl;
	long result = Sort_Count(data, 0, i - 2);
	cout << result << endl;
	return EXIT_SUCCESS;
}
