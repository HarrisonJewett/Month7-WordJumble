#pragma once

//#include "Game.h"
#include <fstream>
#include <iostream>
#include "HTable.h"
#include "Timer.h"
#include "BST.h"


struct singleHighscore
{
	string name;
	string highscore;
};

//#define TABLE_SIZE 4999;

class Game
{
private:
	unsigned int x;
	bool contPlay;
	bool correctGuess;
	unsigned int score;
	unsigned int level;
	string compare;

	singleHighscore HS[5];

	string wordToGuess;
	string typedWord;
	string jumbledWord;
	string remainingLetters;
	string nameForScore;

public:

	Game();
	~Game();

	Timer time;
	
	//Functions
	HTable<string> * hashPointer;
	BST<string> searchTree;
	BST<string> highscores;
	void Play();
	void Update();
	void Render();
	void Load();
	void loadDictionary();
	void endRound();
	void loadHighscore();
	void saveHighscore();
	unsigned int factorial(unsigned int f);
	string jumbleString(string wordToJumble);

};