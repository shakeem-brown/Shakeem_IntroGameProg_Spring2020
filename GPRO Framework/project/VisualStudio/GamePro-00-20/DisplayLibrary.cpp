/*	This file will house the common Display function
 *  Purpose:      Houses the Display funtions for the
				  various games within this frame work.
 *	Contributors: This Library was made in collaboration
				  by Andrew Barnett and Shakeem Brown
 *********************************************************/

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <string>
#include "GamePro-00-20/Fillorino.h"

/*
	Purpose:	Draws the board state using the given height and width
*/
using namespace std;

void displayBoard(char array[], int arraySize, int condition, string newLineArray)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (i != 0)
		{
			if ((i % condition) == 0)
			{
				cout << endl;
				cout << newLineArray << endl;
			}
		}
		cout << array[i];
	}
	cout << endl << endl;
}