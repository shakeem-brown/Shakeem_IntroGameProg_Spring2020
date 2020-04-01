/*	TicTacToe game
 *  Purpose:      Runs the game of TicTacToe using the 
                  framework library
 *	Contributors: This game was made in collaboration
				  by Andrew Barnett and Shakeem Brown
 *********************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include "GamePro-00-20/Fillorino.h"

using namespace std;

//Function Prototypes
bool intChecker(int input, int size);
bool charChecker(char input);
char player1Assign(char choice);
char player2Assign(char P1, char P2);
bool moveChecker(int row, int col, char player);
char spotReturner(int row, int col, char player);
char spot(char spot, int row, int col);
bool playerSwapTurn(bool player);
char player1Swapper(char P1, char P2, bool player);
char player2Swapper(char P1, char P2, bool player);
bool overwriteCheck(int row, int col, char);
bool checkGameState(char spot1, char spot2, char spot3, char spot4, char spot5, char spot6, char spot7, char spot8, char spot9);
bool Win(char player);
bool playAgain(char);
void displayBoard(char array[], int arraySize, int condition, string newLineArray);

const int BOARD_SIZE = 3;
const int ARRAY_SIZE = 30;
const int NEW_LINE = ARRAY_SIZE / BOARD_SIZE;
const string LINE_DIVIDER = "---|---|---";

//TicTacToe Main
int launchTicTacToe()
{
	bool gameEnd = false;

	do {
		system("cls");

		int rowNum = 0;
		int colNum = 0;
		bool invalid = 0;
		char P1 = ' ';
		char P2 = ' ';
		char temp1;
		char temp2;
		bool player = true;
		char spot1 = '1', spot2 = '2', spot3 = '3', spot4 = '4',
			spot5 = '5', spot6 = '6', spot7 = '7', spot8 = '8', spot9 = '9';
		char spotty = ' ';
		bool winCon = false;
		int turn = 0;
		char playagain = ' ';
		char boardArray[] = { ' ', spot1, ' ', '|', ' ', spot2,' ', '|', ' ',
			spot3,' ', spot4, ' ', '|', ' ', spot5,' ', '|', ' ', spot6,' ',
			spot7, ' ', '|', ' ', spot8,' ', '|', ' ', spot9 };
	
		cout << "Welcome to TicTacToe!" << endl << endl;
		do
		{
			cout << " Player 1, do you want X's or O's? ";
			cin >> P1;
			P1 = player1Assign(P1);
			P2 = player2Assign(P1, P2);
			invalid = charChecker(P1);
			cout << endl << endl;
		
		} while (invalid == true);

		cout << "Player 1 is: " << P1 << endl << endl;
		cout << "Player 2 is: " << P2 << endl << endl;
		do
		{
			bool open = true;
			do
			{
				cout << "Enter column from 1-3: ";
				cin >> colNum;
				cout << endl;
				invalid = intChecker(static_cast<int>(colNum), BOARD_SIZE);
			} while (invalid == true);
			do
			{
				cout << "Enter row number from 1-3: ";
				cin >> rowNum;
				cout << endl;
				invalid = intChecker(static_cast<int>(rowNum), BOARD_SIZE);
			} while (invalid == true);

			cout << endl << endl;
			moveChecker(rowNum, colNum, P1);
			spotty = spotReturner(rowNum, colNum, P1);

			if (rowNum == 1 && colNum == 1)
			{
				open = overwriteCheck(rowNum, colNum, spot1);
				if (open == 49) {
					{
						spot1 = spot(spotty, rowNum, colNum);
						boardArray[1] = spot1;
					}
				}
			}
			else if (rowNum == 1 && colNum == 2)
			{
				open = overwriteCheck(rowNum, colNum, spot2);
				if (open == 50)
				{
					spot2 = spot(spotty, rowNum, colNum);
					boardArray[5] = spot2;
				}
			}
			else if (rowNum == 1 && colNum == 3)
			{
				open = overwriteCheck(rowNum, colNum, spot3);
				if (open == 51)
				{
					spot3 = spot(spotty, rowNum, colNum);
					boardArray[9] = spot3;
				}
			}
			else if (rowNum == 2 && colNum == 1)
			{
				open = overwriteCheck(rowNum, colNum, spot4);
				if (open == 52)
				{
					spot4 = spot(spotty, rowNum, colNum);
					boardArray[11] = spot4;
				}
			}
			else if (rowNum == 2 && colNum == 2)
			{
				open = overwriteCheck(rowNum, colNum, spot5);
				if (open == 53)
				{
					spot5 = spot(spotty, rowNum, colNum);
					boardArray[15] = spot5;
				}
			}
			else if (rowNum == 2 && colNum == 3)
			{
				open = overwriteCheck(rowNum, colNum, spot6);
				if (open == 54)
				{
					spot6 = spot(spotty, rowNum, colNum);
					boardArray[19] = spot6;
				}
			}
			else if (rowNum == 3 && colNum == 1)
			{
				open = overwriteCheck(rowNum, colNum, spot7);
				if (open == 55)
				{
					spot7 = spot(spotty, rowNum, colNum);
					boardArray[21] = spot7;
				}
			}
			else if (rowNum == 3 && colNum == 2)
			{
				open = overwriteCheck(rowNum, colNum, spot8);
				if (open == 56)
				{
					spot8 = spot(spotty, rowNum, colNum);
					boardArray[25] = spot8;
				}
			}
			else if (rowNum == 3 && colNum == 3)
			{
				open = overwriteCheck(rowNum, colNum, spot9);
				if (open == 57)
				{
					spot9 = spot(spotty, rowNum, colNum);
					boardArray[29] = spot9;
				}
			}

			displayBoard(boardArray, ARRAY_SIZE, NEW_LINE, LINE_DIVIDER);
			winCon = checkGameState(spot1, spot2, spot3, spot4, spot5, spot6, spot7, spot8, spot9);

			if (winCon == true)
			{
				gameEnd = Win(P1);
				turn--;
			}
			
			if (48 < open && open < 58)
			{
				if (player == true)
				{
					temp1 = player1Swapper(P1, P2, player);
					temp2 = P1;
				}
				if (player == false)
				{
					temp2 = player2Swapper(P1, P2, player);
					temp1 = P2;
				}
				P1 = temp1;
				P2 = temp2;
				player = playerSwapTurn(player);
				turn++;
			}
						
			if (turn == 9)
			{
				cout << "DRAW!" << endl;
			}

		} while (gameEnd == false);
		
		gameEnd = playAgain(playagain);

	} while (gameEnd == false);

	return 0;
}

/*
	Purpose:	Checks player one's player character, X or O.
*/
bool charChecker(char input) {
	if (input != 'O')
	{ 
		if(input != 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return true;
		}
	}
	return false;
}

/*
	Purpose:	Assigns character to player1
*/
char player1Assign(char choice)
{
	char player1 = 'x';
	char player2 = 'o';

	if (choice == 'X' || choice == 'x') {
		player1 = 'X';
		player2 = 'O';
		return player1;
	}
	else if (choice == 'O' || choice == 'o'){
		player1 = 'O';
		player2 = 'X';
	}
	return player1;
}

/*
	Purpose:	Assigns character to player2
*/
char player2Assign(char P1, char P2) {
	if (P1 == 'X')
		P2 = 'O';
	else if (P1 == 'O')
		P2 = 'X';
	return P2;
}

/*
	Purpose:	Checks if the space is open
*/
bool moveChecker(int row, int col, char player)
{
	if (row == 1 && col == 1)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 1 && col == 2)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 1 && col == 3)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 2 && col == 1)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 2 && col == 2)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 2 && col == 3)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 3 && col == 1)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 3 && col == 2)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	else if (row == 3 && col == 3)
	{
		if (player != 'O')
		{
			if (player != 'X')
			{
				cout << "That is an invalid input." << endl;
				cout << "Please try again!" << endl;
				return false;
			}
		}
	}
	return true;
}

/*
	Purpose:	Allows the current player to place in a spot
*/
char spotReturner(int row, int col, char player)
{
	if (row == 1 && col == 1)
	{
		return player;
	}
	else if (row == 1 && col == 2)
	{
		return player;
	}
	else if (row == 1 && col == 3)
	{
		return player;
	}
	else if (row == 2 && col == 1)
	{
		return player;
	}
	else if (row == 2 && col == 2)
	{
		return player;
	}
	else if (row == 2 && col == 3)
	{
		return player;
	}
	else if (row == 3 && col == 1)
	{
		return player;
	}
	else if (row == 3 && col == 2)
	{
		return player;
	}
	else if (row == 3 && col == 3)
	{
		return player;
	}
	else
		return ' ';
}

//Board functions below
//************************************************************

/*
	Purpose:	Places the current player's character on the given spot
*/
char spot(char spot, int row, int col)
{
	if (row == 1 && col == 1)
	{
		return spot;
	}
	else if (row == 1 && col == 2)
	{
		return spot;
	}
	else if (row == 1 && col == 3)
	{
		return spot;
	}
	else if (row == 2 && col == 1)
	{
		return spot;
	}
	else if (row == 2 && col == 2)
	{
		return spot;
	}
	else if (row == 2 && col == 3)
	{
		return spot;
	}
	else if (row == 3 && col == 1)
	{
		return spot;
	}
	else if (row == 3 && col == 2)
	{
		return spot;
	}
	else if (row == 3 && col == 3)
	{
		return spot;
	}
	else
		return ' ';
}

/*
	Purpose:	Swaps player1's character with player2's character
*/
char player1Swapper(char P1, char P2, bool player)
{
	char temp;
	temp = P1;
	P1 = P2;
	P2 = temp;
	return P1;

}

/*
	Purpose:	Swaps player2's character with player1's character
*/
char player2Swapper(char P1, char P2, bool player)
{
	char temp;
	temp = P1;
	P1 = P2;
	P2 = temp;
	return P2;
}

/*
	Purpose:	Checks if the given spot has already been used
*/
bool overwriteCheck(int row, int col, char spotNum) {
	if (row == 1 && col == 1)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 1 && col == 2)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 1 && col == 3)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 2 && col == 1)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 2 && col == 2)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 2 && col == 3)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 3 && col == 1)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 3 && col == 2)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else if (row == 3 && col == 3)
	{
		if (spotNum == 'O')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
		else if (spotNum == 'X')
		{
			cout << "That is an invalid input." << endl;
			cout << "Please try again!" << endl;
			return false;
		}
	}
	else 
		return true;
}

/*
	Purpose:	Checks if the win condition has been met
*/
bool checkGameState(char spot1, char spot2, char spot3, char spot4, char spot5, char spot6, char spot7, char spot8, char spot9) {
	//Horz
	if (spot1 == spot2 && spot2 == spot3)
	{
		return true;
	}
	else if (spot4 == spot5 && spot5 == spot6)
	{
		return true;
	}
	else if (spot7 == spot8 && spot8 == spot9)
	{
		return true;
	}

	//Vert
	else if (spot1 == spot4 && spot4 == spot7)
	{
		return true;
	}
	else if (spot2 == spot5 && spot5 == spot8)
	{
		return true;
	}
	else if (spot3 == spot6 && spot6 == spot9)
	{
		return true;
	}

	//Diag
	else if (spot1 == spot5 && spot5 == spot9)
	{
		return true;
	}
	else if (spot3 == spot5 && spot5 == spot7)
	{
		return true;
	}
	return false;
}
