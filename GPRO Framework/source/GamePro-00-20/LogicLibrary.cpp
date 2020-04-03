/*	This file will house the common logic function
 *  Purpose:      Houses the Logic funtions for the
				  various games within this frame work.
 *	Contributors: This Library was made in collaboration
				  by Andrew Barnett and Shakeem Brown
 *********************************************************/

#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GamePro-00-20/Fillorino.h"

using namespace std;

/*
	Purpose:	Swaps the current player with the other player
*/
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

/*
	Purpose:	Prompts the player if they would like to play again
*/
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

/*
	Purpose:	Displays the player that won
*/
bool Win(char player)
{
	cout << "You Win " << player << "!!!" << endl;
	return true;
}

/*
	Purpose:	Checks players column/row input
*/
bool intChecker(int input, int size) {
	if ((input > size) || (input < 0))
	{
		cout << "That is an invalid input." << endl;
		cout << "Please try again!" << endl;
		return true;
	}
	else if (input == 0)
	{
		cout << "That is an invalid input." << endl;
		cout << "Please try again!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}