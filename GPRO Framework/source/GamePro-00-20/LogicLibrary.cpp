#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GamePro-00-20/Fillorino.h"

using namespace std;

//This file will house the common logic function

//Complete
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

//NextTime
bool playAgain(char input)
{
	bool checker = false;
	do
	{
		cout << "Play Again? (Y/N)" << endl << endl;
		cin >> input;

		if (input == 'N' || input == 'n')
		{
			return true;
		}
		else if (input == 'Y' || input == 'y')
		{
			return false;
		}
		else
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
		}
	} while (checker == false);
	return true;
}

//NextTime
bool Win(char player)
{
	cout << "You Win " << player << "!!!" << endl;
	return true;
}