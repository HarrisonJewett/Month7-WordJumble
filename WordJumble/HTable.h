#pragma once
#include "SLList.h"
#include <cstring>
#include <string>
#include <ctime>
#define TABLE_SIZE 500;

using namespace std;



//template <typename Type> void HTable<Type>::printSomeStuff(const char* filePath);


template <typename Type>
class HTable
{
private:
	SLList<Type>*theTable;
	unsigned int buckets;
	unsigned int(*hFunction)(const Type&v);

public:
	//Default constructor
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		buckets = numOfBuckets;
		theTable = new SLList<Type>[buckets];
		this->hFunction = hFunction;
	}

	//Default deconstructor
	~HTable()
	{
		//clear();
		delete[]theTable;
	}

	//Assignment Operator
	HTable<Type>& operator=(const HTable<Type>& that)
	{
		if (this != &that)
		{
			delete[]theTable;
			theTable = new SLList<Type>[that.buckets];
			buckets = that.buckets;
			for (unsigned int i = 0; i < buckets; ++i)
			{
				table[i] = that.table[i];
				//table[i]->Size = that.table[i]->Size;
			}
			hFunction = that.hFunction;
		}
		return *this;
	}

	//Copy Constructor
	HTable(const HTable<Type>& that)
	{
		buckets = that.buckets;
		theTable = new SLList<Type>[that.buckets];
		for (unsigned int i = 0; i < buckets; ++i)
			table[i] = that.table[i];
		hFunction = that.hFunction;
	}

	//Insert
	void insert(const Type& v)
	{
		unsigned int bucketNeeded = hFunction(v);
		theTable[bucketNeeded].addHead(v);
	}

	//Find and Remove
	bool findAndRemove(const Type& v)
	{
		SLLIter<Type> iter(table[hFunction(v)]);
		iter.begin();
		while (!iter.end())
		{
			if (iter.current() == v)
			{
				table[hFunction(v)].remove(iter);
				return true;
			}
			else
				++iter;
		}
		return false;
	}

	//Clear
	void clear()
	{
		for (unsigned int i = 0; i < buckets; ++i)
			table[i].clear();
	}

	//Find
	int find(const Type& v) const
	{
		SLLIter<Type> iter(theTable[hFunction(v)]);
		iter.begin();
		while (iter.end() == false)
		{
			if (iter.current() == v)
				return hFunction(v);
			else
				++iter;
		}
		return -1;
	}

	string findSixString()
	{
		srand(static_cast<int>(time(0)));
		string sixLetterString = " ";
		while (sixLetterString.length() != 6)
		{
			int RNG = (rand() % 4999);
			int loopingLength = (rand() % theTable[RNG].size() - 1);
			SLLIter<string> Iter(theTable[RNG]);
			Iter.begin();
			for (int i = 0; i < loopingLength && !Iter.end(); ++i, ++Iter);
			sixLetterString = Iter.current();
		}
		return sixLetterString;
	}

	void HTable<Type>::printSomeStuff(const char* filePath = "hashdata.txt")
	{
		// we're gonna need to open a file for all this data
		ofstream outFile(filePath);

		// let's make sure the file got opened
		if (outFile.is_open())
		{
			// number of empty buckets, total count of elements, index of emptiest bucket, index of fullest bucket
			unsigned int empty = 0;
			unsigned int totalCount = 0;
			unsigned int loIndex = 0;
			unsigned int hiIndex = 0;

			// loop through all the buckets
			for (unsigned int i = 0; i < buckets; ++i)
			{
				// add the number of elements in each bucket to the total count
				totalCount += theTable[i].size();
				// print the index of this bucket and its size to the file
				outFile << i << " : " << theTable[i].size() << '\n';

				// if this list is empty, increment the empty count
				if (theTable[i].size() == 0)
					++empty;

				// if this list has less elements than the lowest one recorded so far, store this as the new lowest
				if (theTable[i].size() < theTable[loIndex].size())
					loIndex = i;
				// else, if this list has more elements than the highest one recorded so far, store this as the new highest
				else if (theTable[i].size() > theTable[hiIndex].size())
					hiIndex = i;
			}

			// print the total count of items and number of buckets to the file
			outFile << '\n' << totalCount << " Total items stored in " << buckets << " buckets\n";
			// print the number of empty buckets
			outFile << '\n' << empty << " Buckets are empty\n\n";
			// get the number of elements in the emptiest bucket
			unsigned int Low = theTable[loIndex].size();
			// get the range fullest-emptiest+1
			unsigned int range = theTable[hiIndex].size() - Low + 1;
			// print this info to the file
			outFile << "each bucket contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

			// make a new array to count how many buckets contain each number of items between the emptiest and fullest
			// and initialize each cell to 0
			unsigned int* arr = new unsigned int[range];
			for (unsigned int j = 0; j < range; ++j)
				arr[j] = 0;

			// now we go through and count how many buckets contain each number of items...
			// 3 buckets have 15 items
			// 5 buckets have 16 items
			// etc.
			for (unsigned int k = 0; k < buckets; ++k)
				++arr[theTable[k].size() - Low];

			// now print this data to the file
			for (unsigned int p = 0; p < range; ++p)
				outFile << arr[p] << " buckets have " << p + Low << " items\n";

			// delete the array we made a minute ago, we are done with it
			delete[] arr;
		}
	}

};

// now that the hash table class is written and tested, we can add 
// a method to the hash table to give us some basic information about
// the hash function we have chosen (distribution info, #of empty 
// buckets, etc.)
// in my particular hash table class, my data members are-
//	SLList<Type>* theTable 	- this is the array of lists
//	unsigned int buckets 	- this is the number of buckets
// ...you will want to crtl+h (find and replace) all instances
// of these with variable names that match your own data members

