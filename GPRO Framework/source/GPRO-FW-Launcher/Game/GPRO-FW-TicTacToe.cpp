#include <iostream>
#include <stdio.h>

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

bool IntChecker(int input);
bool CharChecker(char input);
char choose_char(char choice);
char player2Assign(char P1, char P2);
bool moveChecker(int row, int col, char player);
char spotReturner(int row, int col, char player);
char spot(char spot, int row, int col);
char player1Switcher(char P1, char P2);
char player2Switcher(char P1, char P2);
bool overwriteCheck(int row, int col, char);
bool checkGameState(char spot1, char spot2, char spot3, char spot4, char spot5, char spot6, char spot7, char spot8, char spot9);
bool Win(char winner);
bool playAgain(char);
//const int TRUE = 32;

int launchTicTacToe()
{
	gs_tictactoe game;
	gs_tictactoe_reset(game);
	bool gameEnd = false;

	do {
		int rowNum = 0;
		int colNum = 0;
		bool invalid = 0;
		char P1 = ' ';
		char P2 = ' ';
		char temp1;
		char temp2;
		char spot1 = '1', spot2 = '2', spot3 = '3', spot4 = '4',
			spot5 = '5', spot6 = '6', spot7 = '7', spot8 = '8', spot9 = '9';
		char spotty = ' ';
		
		bool winCon = false;
		int turn = 0;
		char playagain = ' ';
		cout << "Welcome to TicTacToe!" << endl << endl;
		do
		{
			cout << " Player 1, do you want X's or O's? ";
			cin >> P1;
			P1 = choose_char(P1);
			P2 = player2Assign(P1, P2);
			invalid = CharChecker(P1);
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
				invalid = IntChecker(colNum);

			} while (invalid == true);
			do
			{
				cout << "Enter row number from 1-3: ";
				cin >> rowNum;
				cout << endl;
				invalid = IntChecker(rowNum);
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


			cout << " " << spot1 << " | " << spot2 << " | " << spot3 << endl;
			cout << "---|---|---" << endl;
			cout << " " << spot4 << " | " << spot5 << " | " << spot6 << endl;
			cout << "---|---|---" << endl;
			cout << " " << spot7 << " | " << spot8 << " | " << spot9 << endl;

			winCon = checkGameState(spot1, spot2, spot3, spot4, spot5, spot6, spot7, spot8, spot9);

			if (winCon == true)
			{
				gameEnd = Win(P1);
				turn--;
			}
			
			//Make the below a function.  Then, put said function inside of each 'spot'!
			if (48 < open && open < 58)
			{
				temp1 = player1Switcher(P1, P2);
				temp2 = player2Switcher(P1, P2);
				P1 = temp1;
				P2 = temp2;
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

bool CharChecker(char input) {
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


bool IntChecker(int input) {
	if ((input > 3) || (input < 0))
	{
		cout << "That is an invalid input." << endl;
		cout << "Please try again!" << endl;
		return true;
	}
	return false;
}
char choose_char(char choice)
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

char player2Assign(char P1, char P2) {
	if (P1 == 'X')
		P2 = 'O';
	else if (P1 == 'O')
		P2 = 'X';
	return P2;
}

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

char player1Switcher(char P1, char P2)
{
	char temp;
	temp = P1;
	P1 = P2;
	P2 = temp;
	return P1;
}

char player2Switcher(char P1, char P2) {
	char temp;
	temp = P1;
	P1 = P2;
	P2 = temp;
	return P2;
}

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
bool Win(char winner)
{
	cout << "You Win " << winner << "!!!" << endl;
	return true;
}

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