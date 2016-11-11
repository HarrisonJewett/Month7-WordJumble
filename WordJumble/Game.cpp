#include "Game.h"
#include <fstream>
#include <iostream>
#include "HTable.h"
#define TABLE_SIZE 500;


using namespace std;

unsigned int hFunction(const string& stringIn)
{
	unsigned long a;
	unsigned long b;
	for (int i = 0; i < stringIn.length(); ++i)
	{
		a += stringIn[i];
		b += stringIn[i] << 1;
	}
	a = (a * b);
	return ~a % TABLE_SIZE;
}

void Play()
{
	unsigned int x = TABLE_SIZE;
	HTable<string> hashin(x, hFunction);
}

void loadDictionary()
{
	ifstream loadFile;
	loadFile.open("engldict.txt");

	if (loadFile.is_open())
	{
		string temp;
		while (!loadFile.eof())
		{
			getline(loadFile, temp);
		}
	}
}