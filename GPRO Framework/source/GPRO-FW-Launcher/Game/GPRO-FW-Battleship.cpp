
#include <iostream>
#include <stdio.h>

using namespace std;

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_BATTLESHIP_PLAYERS				2
#define GS_BATTLESHIP_BOARD_WIDTH			10
#define GS_BATTLESHIP_BOARD_HEIGHT			10

enum gs_battleship_space_state
{
	// invalid space state
	gs_battleship_space_invalid = -1,

	// states visible to both players
	gs_battleship_space_open,			// space is open and unguessed
	gs_battleship_space_miss,			// space was guessed and missed
	gs_battleship_space_hit,			// space was guessed and hit

	// states hidden from opponent player
	gs_battleship_space_patrol2,		// 2-unit patrol boat
	gs_battleship_space_submarine3,		// 3-unit submarine
	gs_battleship_space_destroyer3,		// 3-unit destroyer
	gs_battleship_space_battleship4,	// 4-unit battleship
	gs_battleship_space_carrier5,		// 5-unit carrier
};
#ifndef __cplusplus
typedef		enum gs_battleship_space_state	gs_battleship_space_state;
#endif	// !__cplusplus

// battleship game state
typedef		unsigned char					gs_battleship_index;
typedef		gs_battleship_space_state		gs_battleship[GS_BATTLESHIP_PLAYERS][GS_BATTLESHIP_BOARD_WIDTH][GS_BATTLESHIP_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,z,w,h,d)		(x < w && y < h && z < d)
#define GS_BATTLESHIP_VALID(p,x,y)				GS_VALIDATE_COORDINATE(x,y,p,GS_BATTLESHIP_BOARD_WIDTH,GS_BATTLESHIP_BOARD_HEIGHT,GS_BATTLESHIP_PLAYERS)


inline gs_battleship_space_state gs_checkers_getSpaceState(gs_battleship const game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos]);
	return gs_battleship_space_invalid;
}

inline gs_battleship_space_state gs_checkers_setSpaceState(gs_battleship game, gs_battleship_space_state const state, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos] = state);
	return gs_battleship_space_invalid;
}

inline gs_battleship_index gs_battleship_reset(gs_battleship game)
{
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
				game[player][xpos][ypos] = gs_battleship_space_open;
	total = (player * xpos * ypos);
	return total;
}


bool checkShipState(char* ship, int shipID);
char* carrierShip(bool alive, bool hit, int row, int column, char* ship);
char* battleship(bool alive, bool hit, int row, int column, char* ship);
char* submarine(bool alive, bool hit, int row, int column, char* ship);
char* destroyerShip(bool alive, bool hit, int row, int column, char* ship);
char* cursierShip(bool alive, bool hit, int row, int column, char* ship);
int designBoard(char array[10][10]);
void showOffBoard(bool player, char array[10][10]);
void showDefBoard(bool player, char array[10][10]);
bool playerSwapTurn(bool player);
void placement();


//-----------------------------------------------------------------------------
// DEFINITIONS

int launchBattleship()
{
	gs_battleship game;
	gs_battleship_reset(game);

	bool playerTurn = true;
	char arrayBoard[10][10];
	bool ship1 = true, ship2 = true, ship3 = true, ship4 = true, ship5 = true;
	char carrier[] = { '5','5','5','5','5' }; 
	char battleship[] = { '4', '4', '4', '4' }; 
	char destroyer[] = { '3','3','3' }; 
	char submarine[] = { '3','3','3' }; 
	char cruiser[] = { '2','2' };
	int cruiserID = 1;
	int submarineID = 2;
	int destroyerID = 3;
	int battleshipID = 4;
	int carrierID = 5;


	designBoard(arrayBoard);
	showOffBoard(playerTurn, arrayBoard);
	playerSwapTurn(playerTurn);

	if (ship1 == false && ship2 == false && ship3 == false && ship4 == false && ship5 == false)
	{
		cout << "You Win!";
	}

	return 0;
}

//
//Ship based functions
bool checkShipState(char* ship, int shipID)
{
	char destroyed2[2] = { 'X', 'X' };
	char destroyed3[3] = { 'X', 'X', 'X' };
	char destroyed4[4] = { 'X', 'X' , 'X', 'X' };
	char destroyed5[5] = { 'X', 'X' , 'X', 'X', 'X' };

	if (shipID == 1)
	{
		if (ship == destroyed2)
		{
			return false;
		}
	}
	else if (shipID == 2)
	{
		if (ship == destroyed3)
		{
			return false;
		}
	}
	else if (shipID == 3)
	{
		if (ship == destroyed3)
		{
			return false;
		}
	}
	else if (shipID == 4)
	{
		if (ship == destroyed4)
		{
			return false;
		}
	}
	else if (shipID == 5)
	{
		if (ship == destroyed5)
		{
			return false;
		}
	}
	else
		return true;
}
char* carrierShip(bool alive, bool hit, int row, int column, char* ship)
{
	alive = true;
	int amountHit = 0;
	
	
	if (hit == true)
	{
		*(ship + amountHit) = 'X';
		amountHit++;
	}
	
	return ship;
}
char* battleship(bool alive, bool hit, int row, int column, char* ship)
{
	alive = true;
	int amountHit = 0;


	if (hit == true)
	{
		*(ship + amountHit) = 'X';
		amountHit++;
	}
	return ship;
}
char* submarine(bool alive, bool hit, int row, int column, char* ship)
{
	alive = true;
	int amountHit = 0;


	if (hit == true)
	{
		*(ship + amountHit) = 'X';
		amountHit++;
	}
	return ship;
}
char* destroyerShip(bool alive, bool hit, int row, int column, char* ship)
{
	alive = true;
	int amountHit = 0;


	if (hit == true)
	{
		*(ship + amountHit) = 'X';
		amountHit++;
	}
	return ship;
}
char* cursierShip(bool alive, bool hit, int row, int column, char* ship)
{
	alive = true;
	int amountHit = 0;


	if (hit == true)
	{
		*(ship + amountHit) = 'X';
		amountHit++;
	}
	return ship;
}
//Board based functions
int designBoard(char array[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			array[i][j] = '+';
		}
	}
	return 0;
}
void placement()
{
	bool valid = true;
	do
	{
		int choice;
		int row = 0;
		int column = 0;

		cout << "Would you like to place the Carrier horizontal(1) or vertical(2)?" << endl;
		cin >> choice;
		if (choice == 1)
		{
			//Horz
			cout << "Which row? (1-10): ";
			cin >> row;
			do
			{
				if (row > 10 || row < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which column is the first spot? (1-10): ";
					cin >> column;
					do
					{
						if (column > 10 || column < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (column > 10 || column < 0);
				}
			} while (row > 10 || row < 0);
		}
		else if (choice == 2)
		{
			//Vert
			cout << "Which column? (1-10): ";
			cin >> column;
			do
			{
				if (column > 10 || column < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which row is the first spot? (1-10): ";
					cin >> row;
					do
					{
						if (row > 10 || row < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (row > 10 || row < 0);
				}
			} while (column > 10 || column < 0);
		}
		else
		{
			cout << "Invalid Choice!" << endl;
			cout << "Please try again!" << endl;
			valid = false;
		}
	} while (valid != false);

}
void showDefBoard(bool player, char array[10][10])
{
	if (player == true) //Player 1
	{
		cout << "P1's Board" << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << " " << array[i][j];
				if (j == 9)
				{
					cout << endl;
				}
			}
		}
	}
	else //Player 2
	{
		cout << "P2's Board" << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << " " << array[i][j];
				if (j == 9)
				{
					cout << endl;
				}
			}
		}
	}
}
void showOffBoard(bool player, char array[10][10])
{
	if (player == true) //Player 1
	{
		cout << "P1's Board" << endl;
		for (int i = 0; i < 10; i++)
		{ 
			for (int j = 0; j < 10; j++)
			{
				cout << " " << array[i][j];
				if (j == 9)
				{
					cout << endl;
				}
			}
		}
	}
	else //Player 2
	{
		cout << "P2's Board" << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << " " << array[i][j];
				if (j == 9)
				{
					cout << endl;
				}
			}
		}
	}
}
//Turn Function
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

//-----------------------------------------------------------------------------		cin >> xPos >> junk >> YPos;   (_, _)