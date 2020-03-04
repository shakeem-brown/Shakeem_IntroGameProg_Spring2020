// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
int launchTicTacToe();
int launchBattleship();
using namespace std;

int main()
{
	int choice = 0;
	bool valid = true;
	do
	{
		cout << "What game do you want to play?" << endl;
		cout << "1) TicTacToe" << endl;
		cout << "2) Battleship" << endl;
		cout << "The Choice: ";
		cin >> choice;
		system("cls");
		if (choice == 1)
		{
			launchTicTacToe();
			valid = false;
		}
		else if (choice == 2)
		{
			launchBattleship();
			valid = false;
		}
		else
		{
			cout << "Invalid Choice!" << endl;
			cout << "Pleas try again!" << endl;
			valid = false;
		}
	} while (valid != false);
	
	return 0;
}
