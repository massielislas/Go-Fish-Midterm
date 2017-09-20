/*Massiel Islas-Malanco
Proffessor Burton
CS 235 Winter 2017 Midterm.*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cmath>
#include <fstream>
#include "FishGame.h"
#include "DisplayFunctions.h"

using namespace std;

void displayMenu()
{
	cout << "Select option:" << endl
		<< "1. Create deck" << endl
		<< "2. Display deck" << endl
		<< "3. Play" << endl
		<< "4. Quit" << endl;
}

int main()
{
	int option = 0;
	FishGame game;
	DisplayFunctions mine;
	string fileName;
	int initialCardSize = 0;
	int deckSize = 0; //variable isn't continously updated. It is not always a reliable count of the cards in the deck.

	do
	{

		mine.displayAsciiArt();
		displayMenu();
		cin >>  option;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter a number (1-4)." << endl << endl;
		}

		else if (option < 1 || option > 4)
		{
			cout << "Please enter a valid number (1-4)." << endl << endl;
		}

		else if (option == 1)
		{
			cout << "What is the name of the file you would like to open?" << endl;
			cin >> fileName;

			deckSize = game.createDeck(fileName);
		}

		else if (option == 2)
			game.displayDeck();

		else if (option == 3)
		{
			cout << "What would you like the initial card size to be?" << endl;
			cin >> initialCardSize;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input" << endl << endl;
			}

			else if (initialCardSize > (deckSize / 2)) //checking to see if deck is large enough for two hands of this size
			{
				while (initialCardSize > (deckSize / 2) && initialCardSize > 0)
				{
					cout << "There are not enough cards on deck for this initial hand size." << endl 
							<< "Please enter another hand size, or enter \"0\" to go back to the main menu" << endl;
					cin >> initialCardSize;
				}

				if (initialCardSize > 0)
					game.play(initialCardSize);
			}

			else
				game.play(initialCardSize);
		}

	} while (option != 4);

	cout << "GOODBYE! Thanks for playing!" << endl;
	system("pause");
	return 0;
}
