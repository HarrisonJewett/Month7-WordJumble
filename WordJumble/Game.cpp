#include "Game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

Game::Game()
{
	contPlay = true;
	correctGuess = false;
	score = 0;
	level = 1;
}


unsigned int hFunction(const string& stringIn)
{
	unsigned long a = 0;
	unsigned long b = 1;
	for (unsigned int i = 0; i < stringIn.length(); ++i)
	{
		a += stringIn[i] * 2;
		b *= stringIn[i] << 1;
		b = ~b << 1;
	}
	a = (a*b);
	return (a*b) % 4999;
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
			if (temp.length() > 2 && temp.length() < 7 && temp.find('\'') == string::npos)
				hashPointer->insert(temp);

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

string Game::jumbleString(string wordToJumble)
{	
	char temp;
	int RNG;
	for (unsigned int i = 0; i < 6; ++i)
	{
		RNG = rand() % 6;
		temp = wordToJumble[RNG];
		wordToJumble[RNG] = wordToJumble[i];
		wordToJumble[i] = temp;
	}

	return wordToJumble;
}

void Game::Play()
{
	wordToGuess = hashPointer->findSixString();
	jumbledWord = jumbleString(wordToGuess);
	remainingLetters = jumbledWord;
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
		{
			if (remainingLetters.find(input) != string::npos)
			{
				typedWord += tolower(input);
				remainingLetters.erase(remainingLetters.find(input), 1);
			}
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		contPlay = false;
		return;
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		if (!searchTree.find(typedWord))
		{
			if (hashPointer->find(typedWord) != -1)
			{
				searchTree.insert(typedWord);
				score += typedWord.length() * level;
			}

			if (wordToGuess == typedWord)
				correctGuess = true;
		}
		
		while (typedWord.length() > 0)
		{
			remainingLetters.push_back(typedWord[typedWord.length() - 1]);
			typedWord.pop_back();
		}
	}
	if (GetAsyncKeyState(VK_BACK))
	{
		if (typedWord.length() >= 1)
		{
			remainingLetters.push_back(typedWord[typedWord.length() - 1]);
			typedWord.pop_back();
		}
	}
}

void Game::Render()
{
	system("cls");

	cout << "Time remaining:" << 60 - time.getElapsedTime()/1000 << "      Score:" << score <<"\n\n";
	cout << jumbledWord << "    " << wordToGuess;	

	cout << '\n' << typedWord;

	cout << "\n\nRemaining Letters: " << remainingLetters;
	cout << "\n\n\nWords Guessed: ";

	searchTree.printInOrder();

	Sleep(140);

	if (time.getElapsedTime() > 60000)
	{
		if (!correctGuess)
			cout << "\n\nThe correct guess was " << wordToGuess << "\nYour final score was: " << score;
			
		endRound();
	}
}

void Game::endRound()
{
	if (correctGuess)
		cout << "\n\nCongragulations, you won the round! Would you like to continue? \nPress Enter to proceed to level " << level + 1 << ". Press ESC to quit";
	else
		cout << "\n\nPress ENTER to try again, press ESC to quit";

	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			if (correctGuess)
				level++;
			else
				score = 0;
			wordToGuess = hashPointer->findSixString();
			jumbledWord = jumbleString(wordToGuess);
			remainingLetters = jumbledWord;
			correctGuess = false;
			searchTree.clear();
			time.reset();
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			contPlay = false;
			break;
		}
	}
}