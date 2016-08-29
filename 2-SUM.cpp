#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;


class HashEntry {
	private:
		long key;
		long value;
	public:
		HashEntry(long key_val, long value_val) {
			this->key = key_val;
			this->value = value_val;
		}

		long getKey() {
			return key;
		}

		long getValue() {
			return value;
		}
};


const long TABLE_SIZE = 1500000;
//const long TABLE_SIZE = 31;
const long FILE_SIZE = 1000000;
//const long FILE_SIZE = 15;
const long bound = 10000;

class HashMap {
	private:
		HashEntry **table;
	public:
		HashMap() {
			table = new HashEntry*[TABLE_SIZE];
			for (long i = 0; i < TABLE_SIZE; i++)
				table[i] = NULL;
		}



		long get(long key) {
			long hash = (key % TABLE_SIZE);
			if(hash < 0)
			{
				hash += TABLE_SIZE;
			}
			while (table[hash] != NULL && table[hash]->getKey() != key)
				hash = (hash + 1) % TABLE_SIZE;
			if (table[hash] == NULL)
				return -1;
			else
				return table[hash]->getValue();
		}

		void put(long key, long value) {
			long hash = (key % TABLE_SIZE);
			if(hash < 0)
			{
				hash += TABLE_SIZE;
			}
			while (table[hash] != NULL && table[hash]->getKey() != key)
				hash = (hash + 1) % TABLE_SIZE;
			if (table[hash] != NULL)
				delete table[hash];
			table[hash] = new HashEntry(key, value);
		} 



		~HashMap() {
			for (long i = 0; i < TABLE_SIZE; i++)
				if (table[i] != NULL)
					delete table[i];
			delete[] table;
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

	HashMap hash_table;
	long *keys = (long *)malloc(sizeof(long) * FILE_SIZE);
	long i;
	for(i = 0; i < FILE_SIZE; i ++)
	{
//		cout << "here" << endl;
		ss >> keys[i];
		hash_table.put(keys[i], 1);
	}
	long t;
	long count = 0;
//	cout << "ok" << endl;
//	cout << -68037553429 % TABLE_SIZE << endl;
//	cout << hash_table.get(-68037553429) << endl;
	for(t = -1 * bound ; t <= bound; t ++)
	{
		cout << t << endl;
		for(i = 0; i < FILE_SIZE; i ++)
		{
//			cout << "i = " << i << " t-i= " << t - keys[i] << endl;
			if(hash_table.get(t - keys[i]) == 1 && ((t - keys[i]) != keys[i]))
			{
				count ++;
				break;
			}
		}
//		cout << count << endl;
	}

	cout << count << endl;


}
