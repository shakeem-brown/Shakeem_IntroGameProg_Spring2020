#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GamePro-00-20/Fillorino.h"

//This file will house the common logic function

bool playerSwapTurn(bool player)
{
	if (player == true)
	{
		player = false;
	}
	else
	{
		player = true;
	}
	return player;
}

void drawBoard(int width, int height, char v[]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			char v[] = {i};
		}
	}
}

using namespace std;

void game()
{
	srand(time(0));
	int myage = rand() % 30;
	int guess = 0;
	int tries = 5;
	bool playagain = 1;

	do
	{
		cout << "Guess my age between 0 and 30?" << endl;
		cout << "You only have five tries." << endl << endl;
		do
		{
			cout << "Enter Guess: ";
			cin >> guess;
			if ((guess == myage) && (tries > 0))
			{
				cout << "You Win!" << endl << endl;
				cout << "Would you like to play again?" << endl;
				cout << "Press 1 to play again." << endl;
				cout << "Press 0 to quit." << endl;
				cin >> playagain;
				system("cls");
				myage = rand() % 30;
				tries = 5;
			}
			else
			{
				if (guess > myage)
				{
					cout << "Lower" << endl;
					tries--;
					cout << "You have " << tries << " tries." << endl << endl;
				}
				else
				{
					cout << "Higher" << endl;
					tries--;
					cout << "You have " << tries << " tries." << endl << endl;
				}
			}
		} while (tries > 0);

		if (tries == 0)
		{
			cout << "You Lose!" << endl;
			cout << "Would you like to play again?" << endl;
			cout << "Press 1 to play again." << endl;
			cout << "Press 0 to quit." << endl;
			cin >> playagain;
		}
		if (playagain == 0)
		{
			playagain = 0;
		}

	} while (playagain != 0);
}

