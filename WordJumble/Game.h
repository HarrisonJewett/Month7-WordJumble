#pragma once

#include "Game.h"
#include <fstream>
#include <iostream>
#include "HTable.h"
#include "Timer.h"


//#define TABLE_SIZE 4999;

class Game
{
private:
	unsigned int x;
	bool contPlay;
	string wordToGuess;
	string typedWord;

public:

	Game();
	~Game();

	Timer time;
	
	//Functions
	HTable<string> * hashPointer;
	void Play();
	void Update();
	void Render();
	void Load();
	void loadDictionary();

};