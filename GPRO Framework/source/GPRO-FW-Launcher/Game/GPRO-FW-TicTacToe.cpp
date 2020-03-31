/*	TicTacToe game
 *  Purpose:      Runs the game of TicTacToe using the 
                  framework library
 *	Contributors: This game was made in collaboration
				  by Andrew Barnett and Shakeem Brown
 *********************************************************/

#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GamePro-00-20/Fillorino.h"

using namespace std;
//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};
#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}

//-----------------------------------------------------------------------------
// DEFINITIONS

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

//TicTacToe Main
int launchTicTacToe()
{
	gs_tictactoe game;
	gs_tictactoe_reset(game);
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
		int board_size = 3;

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
				invalid = intChecker(static_cast<int>(colNum), board_size);
			} while (invalid == true);
			do
			{
				cout << "Enter row number from 1-3: ";
				cin >> rowNum;
				cout << endl;
				invalid = intChecker(static_cast<int>(rowNum), board_size);
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
					}
				}
			}
			else if (rowNum == 1 && colNum == 2)
			{
				open = overwriteCheck(rowNum, colNum, spot2);
				if (open == 50)
				{
					spot2 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 1 && colNum == 3)
			{
				open = overwriteCheck(rowNum, colNum, spot3);
				if (open == 51)
				{
					spot3 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 2 && colNum == 1)
			{
				open = overwriteCheck(rowNum, colNum, spot4);
				if (open == 52)
				{
					spot4 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 2 && colNum == 2)
			{
				open = overwriteCheck(rowNum, colNum, spot5);
				if (open == 53)
				{
					spot5 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 2 && colNum == 3)
			{
				open = overwriteCheck(rowNum, colNum, spot6);
				if (open == 54)
				{
					spot6 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 3 && colNum == 1)
			{
				open = overwriteCheck(rowNum, colNum, spot7);
				if (open == 55)
				{
					spot7 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 3 && colNum == 2)
			{
				open = overwriteCheck(rowNum, colNum, spot8);
				if (open == 56)
				{
					spot8 = spot(spotty, rowNum, colNum);
				}
			}
			else if (rowNum == 3 && colNum == 3)
			{
				open = overwriteCheck(rowNum, colNum, spot9);
				if (open == 57)
				{
					spot9 = spot(spotty, rowNum, colNum);
				}
			}

			//Make draw board function Here
			cout << " " << spot1 << " | " << spot2 << " | " << spot3 << endl;
			cout << "---|---|---" << endl;
			cout << " " << spot4 << " | " << spot5 << " | " << spot6 << endl;
			cout << "---|---|---" << endl;
			cout << " " << spot7 << " | " << spot8 << " | " << spot9 << endl;
			// Do this next ^^^^

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
