#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char** argv)
{
	Game gp;

	cout << "Loading...\n" << "0/22";

	gp.Load();
	gp.Play();


	return 0;
}