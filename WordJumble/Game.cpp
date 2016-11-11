#include "Game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

Game::Game()
{
	contPlay = true;
}


unsigned int hFunction(const string& stringIn)
{
	unsigned long a = 0;
	unsigned long b = 1;
	for (int i = 0; i < stringIn.length(); ++i)
	{
		a += stringIn[i];
		b *= stringIn[i];
		b = b << 1;
	}
	//a = (a*b);
	return (~a*~b) % 4999;
}

Game::~Game()
{

}

void Game::Load()
{
	hashPointer = new HTable<string>(4999, hFunction);
	loadDictionary();
}

void Game::loadDictionary()
{
	unsigned int writeLoading = 0;
	unsigned int loadPercent = 0;
	ifstream loadFile;
	loadFile.open("engldict.txt");

	if (loadFile.is_open())
	{
		string temp;
		while (!loadFile.eof())
		{
			getline(loadFile, temp);
			if (temp.length() > 2 && temp.length() < 7 && temp.find('\'') == -1)
			{
				hashPointer->insert(temp);
			}
			++writeLoading;

			if (writeLoading % 4999 == 0)
			{
				loadPercent++;
				system("cls");
				cout << "Loading...\n" << loadPercent << "/22";
			}
		}
		hashPointer->printSomeStuff();
		loadFile.close();
	}
}

void Game::Play()
{
	wordToGuess = hashPointer->findSixString();
	typedWord = "";
	time.reset();


	while (contPlay)
	{
		Update();
		Render();
	}
}

void Game::Update()
{
	if (_kbhit())
	{
		char input = _getch();

		if (-32 == input)
			_getch();

		else if (isalpha(input))
			typedWord += tolower(input);
	}


	if (GetAsyncKeyState(VK_ESCAPE))
	{
		contPlay = false;
		return;
	}
	if (GetAsyncKeyState(VK_RETURN))
	{

	}
	if (GetAsyncKeyState(VK_BACK))
	{
		if (typedWord.length() >= 1)
			typedWord.pop_back();
	}
}

void Game::Render()
{
	system("cls");

	cout << "Time remaining:" << 120 - time.getElapsedTime()/1000 << "\n\n";
	cout << wordToGuess;
	cout << '\n' << typedWord;

	Sleep(120);
}