#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GamePro-00-20/Fillorino.h"

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
char* carrierShip(bool alive, bool hit, int* row, int* column, char* ship, int ID);
char* battleshipShip(bool alive, bool hit, int* row, int* column, char* ship, int ID);
char* submarineShip(bool alive, bool hit, int* row, int* column, char* ship, int ID);
char* destroyerShip(bool alive, bool hit, int* row, int* column, char* ship, int ID);
char* cruiserShip(bool alive, bool hit, int* row, int* column, char* ship, int ID);
int designBoard(char array[10][10]);
void showOffBoard(bool player, char array[10][10]);
void showDefBoard(bool player, char array[10][10], int*& row, int*& column);
bool playerSwapTurn(bool player);
void placement(int*& row, int*& column);
char* modifyDefBoard(bool player, static char array[][10], int*& row, int*& column, char ship1[5], char ship2[5], char ship3[5], char ship4[5], char ship5[5]);
void displayBoard(char array[], int arraySize, int condition, string newLineArray);

//-----------------------------------------------------------------------------
// DEFINITIONS

int launchBattleship()
{
	gs_battleship game;
	gs_battleship_reset(game);

	const int boardRow = 10;
	const int boardColumn = 10;

	bool playerTurn = true;
	bool hit = false;
	bool destroyed = false;
	char arrayBoard[boardRow][boardColumn];
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
	int row[5], column[5];
	int* rowPtr = row;
	int* colPtr = column;
	char** tempArray = 0;
	//Beginning of code that would be moved to a "buildBoard" function.
	tempArray = new char* [boardRow];

	designBoard(arrayBoard);

	placement(rowPtr, colPtr);

	for (int i = 0; i < 10; i++) 
	{
		tempArray[i] = new char[boardColumn];
		for (int j = 0; j < 10; j++) 
		{
			tempArray[i][j] = arrayBoard[i][j];
		}
	}
		
	**tempArray = *modifyDefBoard(playerTurn, arrayBoard, rowPtr, colPtr, carrier, battleship, submarine, destroyer, cruiser);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arrayBoard[i][j] = tempArray[i][j];
			cout << arrayBoard[i][j];
		}
		cout << endl;
	}
	//End of code that would be moved to a "buildBoard" function.
	carrierShip(destroyed, hit, row, column, carrier, carrierID);
	battleshipShip(destroyed, hit, row, column, battleship, battleshipID);
	submarineShip(destroyed, hit, row, column, submarine, submarineID);
	destroyerShip(destroyed, hit, row, column, destroyer, destroyerID);
	cruiserShip(destroyed, hit, row, column, cruiser, cruiserID);
	
	showOffBoard(playerTurn, arrayBoard);
	playerSwapTurn(playerTurn);

	if (ship1 == false && ship2 == false && ship3 == false && ship4 == false && ship5 == false)
	{
		cout << "You Win!";
	}
	delete[] tempArray;
	return 0;
	
}
//
//State based function
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
bool checkHit(int& row, int& column, int ID) {
	bool hit = false;
	if (ID == 1) {
		if (row < 11 || row > 0 )
		{
			if (column < 11 || column > 0)
			{
				hit = true;
			}
		}
	}
	else if (ID == 2)
	{
		if (row < 11 || row > 0)
		{
			if (column < 11 || column > 0)
			{
				hit = true;
			}
		}
	}
	else if (ID == 3)
	{
			if (row < 11 || row > 0)
			{
				if (column < 11 || column > 0)
				{
					hit = true;
				}
			}
	}
	else if (ID == 4)
	{
		if (row < 11 || row > 0)
		{
			if (column < 11 || column > 0)
			{
				hit = true;
			}
		}
	}
	else if (ID == 5)
	{
		if (row < 11 || row > 0)
		{
			if (column < 11 || column > 0)
			{
				hit = true;
			}
		}
	}
	return hit;
}
//Ship based functions
char* carrierShip(bool alive, bool hit, int* row, int* column, char* ship, int ID)
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
char* battleshipShip(bool alive, bool hit, int* row, int* column, char* ship, int ID)
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
char* submarineShip(bool alive, bool hit, int* row, int* column, char* ship, int ID)
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
char* destroyerShip(bool alive, bool hit, int* row, int* column, char* ship, int ID)
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
char* cruiserShip(bool alive, bool hit, int* row, int* column, char* ship, int ID)
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
//Make board functions
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
void placement(int*& row, int*& column)
{
	bool valid = true;
	int choice;

	int tempRow = 0;
	int tempCol = 0;
	for (int shipID = 0; shipID < 5; shipID++)
	{
		do
		{
		string shipname[5] = { "Cruiser", "Submarine", "Destroyer", "Battleship", "Carrier" };
		cout << "Would you like to place the " << shipname[shipID] << " horizontal(1) or vertical(2)?";
		cin >> choice;

			if (choice == 1)
			{
				//Horz
				cout << "Which row? (1-10): ";
				cin >> tempRow;
				*(row + shipID) = tempRow;
				do
				{
					if (tempRow > 10 || tempRow < 0)
					{
						cout << "Invalid Choice!" << endl;
						cout << "Please try again!" << endl;
					}
					else
					{
						cout << "Which column is the first spot? (1-10): ";
						cin >> tempCol;
						*(column + shipID) = tempCol;
						do
						{
							if (tempCol > 10 || tempCol < 0) {
								cout << "Invalid Choice!" << endl;
								cout << "Please try again!" << endl;
							}
						} while (tempCol > 10 || tempCol < 0);
						cout << endl << endl;
					}
				} while (tempRow > 10 || tempRow < 0);
			}
			else if (choice == 2)
			{
				//Vert
				cout << "Which column? (1-10): ";
				cin >> tempCol;
				*(column + shipID) = tempCol;
				do
				{
					if (tempCol > 10 || tempCol < 0)
					{
						cout << "Invalid Choice!" << endl;
						cout << "Please try again!" << endl;
					}
					else
					{
						cout << "Which row is the first spot? (1-10): ";
						cin >> tempRow;
						*(row + shipID) = tempRow;
						do
						{
							if (tempRow > 10 || tempRow < 0) {
								cout << "Invalid Choice!" << endl;
								cout << "Please try again!" << endl;
							}
						} while (tempRow > 10 || tempRow < 0);
						cout << endl << endl;
					}
				} while (tempCol > 10 || tempCol < 0);
			}
			else
			{
				cout << "Invalid Choice!" << endl;
				cout << "Please try again!" << endl;
				valid = false;
			}
		} while (valid == false);
	}
}
char* modifyDefBoard(bool player, static char array[][10], int*& row, int*& column, char ship1[5], char ship2[5], char ship3[5], char ship4[5], char ship5[5]) {
	int shipRow = 0;
	int shipCol = 0;
	int shipID = 0;
	if (player == true) 
	{
		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship1 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship2 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship3 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship4 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship5 + shipID);
	}

	else 
	{
		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship1 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship2 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship3 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship4 + shipID);
		shipID++;

		shipRow = *(row + shipID);
		shipCol = *(column + shipID);
		array[shipRow][shipCol] = *(ship5 + shipID);
	}
	return array[10];
}
//Show board functions
void showDefBoard(bool player, char array[10][10], int*& row, int*& column)
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
/*
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
*/

//
//-----------------------------------------------------------------------------		cin >> xPos >> junk >> YPos;   (_, _)
/*
void stuff(){
			if (shipID == 2) {
			cout << "Would you like to place the " << shipname[shipID] << " horizontal(1) or vertical(2)?" << endl;
			cin >> choice;
			if (choice == 1)
			{
			//Horz
			cout << "Which row? (1-10): ";
			cin >> *row;
			do
			{
				if (*row > 10 || *row < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which column is the first spot? (1-10): ";
					cin >> *column;
					do
					{
						if (*column > 10 || *column < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*column > 10 || *column < 0);
				}
			} while (*row > 10 || *row < 0);
			}
			else if (choice == 2)
			{
			//Vert
			cout << "Which column? (1-10): ";
			cin >> *column;
			do
			{
				if (*column > 10 || *column < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which row is the first spot? (1-10): ";
					cin >> *row;
					do
					{
						if (*row > 10 || *row < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*row > 10 || *row < 0);
				}
			} while (*column > 10 || *column < 0);
			}
			else
			{
			cout << "Invalid Choice!" << endl;
			cout << "Please try again!" << endl;
			valid = false;
			}
			}
			if (shipID == 3) {
			cout << "Would you like to place the " << shipname[shipID] << " horizontal(1) or vertical(2)?" << endl;
			cin >> choice;
			if (choice == 1)
			{
			//Horz
			cout << "Which row? (1-10): ";
			cin >> *row;
			do
			{
				if (*row > 10 || *row < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which column is the first spot? (1-10): ";
					cin >> *column;
					do
					{
						if (*column > 10 || *column < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*column > 10 || *column < 0);
				}
			} while (*row > 10 || *row < 0);
			}
			else if (choice == 2)
			{
			//Vert
			cout << "Which column? (1-10): ";
			cin >> *column;
			do
			{
				if (*column > 10 || *column < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which row is the first spot? (1-10): ";
					cin >> *row;
					do
					{
						if (*row > 10 || *row < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*row > 10 || *row < 0);
				}
			} while (*column > 10 || *column < 0);
			}
			else
			{
			cout << "Invalid Choice!" << endl;
			cout << "Please try again!" << endl;
			valid = false;
			}
			}	if (shipID == 4) {
			cout << "Would you like to place the " << shipname[shipID] << " horizontal(1) or vertical(2)?" << endl;
			cin >> choice;
			if (choice == 1)
			{
			//Horz
			cout << "Which row? (1-10): ";
			cin >> *row;
			do
			{
				if (*row > 10 || *row < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which column is the first spot? (1-10): ";
					cin >> *column;
					do
					{
						if (*column > 10 || *column < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*column > 10 || *column < 0);
				}
			} while (*row > 10 || *row < 0);
			}
			else if (choice == 2)
			{
			//Vert
			cout << "Which column? (1-10): ";
			cin >> *column;
			do
			{
				if (*column > 10 || *column < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which row is the first spot? (1-10): ";
					cin >> *row;
					do
					{
						if (*row > 10 || *row < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*row > 10 || *row < 0);
				}
			} while (*column > 10 || *column < 0);
			}
			else
			{
			cout << "Invalid Choice!" << endl;
			cout << "Please try again!" << endl;
			valid = false;
			}
			}	if (shipID == 5) {
			cout << "Would you like to place the " << shipname[shipID] << " horizontal(1) or vertical(2)?" << endl;
			cin >> choice;
			if (choice == 1)
			{
			//Horz
			cout << "Which row? (1-10): ";
			cin >> *row;
			do
			{
				if (*row > 10 || *row < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which column is the first spot? (1-10): ";
					cin >> *column;
					do
					{
						if (*column > 10 || *column < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*column > 10 || *column < 0);
				}
			} while (*row > 10 || *row < 0);
			}
			else if (choice == 2)
			{
			//Vert
			cout << "Which column? (1-10): ";
			cin >> *column;
			do
			{
				if (*column > 10 || *column < 0)
				{
					cout << "Invalid Choice!" << endl;
					cout << "Please try again!" << endl;
				}
				else
				{
					cout << "Which row is the first spot? (1-10): ";
					cin >> *row;
					do
					{
						if (*row > 10 || *row < 0) {
							cout << "Invalid Choice!" << endl;
							cout << "Please try again!" << endl;
						}
					} while (*row > 10 || *row < 0);
				}
			} while (*column > 10 || *column < 0);
			}
			else
			{
			cout << "Invalid Choice!" << endl;
			cout << "Please try again!" << endl;
			valid = false;
			}
			}
		}
*/