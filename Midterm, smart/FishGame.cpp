/*Massiel Islas-Malanco
Proffessor Burton
CS 235 Winter 2017 Midterm.*/

#pragma once
#include <fstream>
#include <iostream>
#include "FishGame.h"
#include <cmath>
#include <ctime>
#include <sstream>

void FishGame::displayMenu()
{
	cout << "1. Make Guess" << endl
		<< "2. Shuffle Deck" << endl
		<< "3. Display Deck" << endl
		<< "4. Display Computer Hand" << endl
		<< "5. Give Up" << endl;
}

bool FishGame::checkSizes()
{

	if (deck.size() == 0)
		return false;

	else if (playerHand.size() == 0)
		return false;

	else if (computerHand.size() == 0)
		return false;

	return true;
}

void FishGame::endGame()
{
	if (computerHand.size() == 0 && playerHand.size() == 0)
	{
		cout << "Both players ran out of cards!" << endl;
		playerScore += 3;
		computerScore += 3;
	}

	else if (computerHand.size() == 0)
	{
		cout << "The computer ran out of cards!" << endl;
		computerScore += 3;
	}

	else if (playerHand.size() == 0)
	{
		cout << "You ran out of cards!" << endl;
		playerScore += 3;
	}

	else if(deck.size() == 0)
	{
		cout << "Deck ran out of cards!" << endl;
	}

	cout << "AND THE WINNER IS......................." << endl;

	if (playerScore > computerScore)
	{
		cout << "YOU!" << endl;
	}

	else if (computerScore > playerScore)
	{
		cout << "... the computer. Sorry! Better luck next time!" << endl;
	}

	else if (computerScore == playerScore)
	{
		cout << "It's a tie!" << endl;
	}

	playerHand.clear();
	computerHand.clear();
	playerScore = 0;
	computerScore = 0;
}

bool FishGame::isNumber(string t)
{
	bool thisIsNumber = true;

	for (int count = 0; count < t.length(); count++)
	{
		if (isdigit(t[count]) == false)
		{
			thisIsNumber = false;
		}
	}

	return thisIsNumber;
}

void FishGame::deletePairs(string whichHand)
{
	int howManyTimes = 0;
	string checking;
	int spot = 0;
	int originalSize = 0;

	if (whichHand == "player")
	{
		while(spot <  playerHand.size())
		{
			originalSize = playerHand.size();
			checking = playerHand.at(spot);
			if(playerHand.occurrences(checking) >= 2)
			{
				playerHand.remove(checking);
				playerHand.remove(checking);
			}
			if(originalSize == playerHand.size())
				spot++;
		}
	}

	else if (whichHand == "computer")
	{
		while(spot <  computerHand.size())
		{
			originalSize = computerHand.size();
			checking = computerHand.at(spot);
			if(computerHand.occurrences(checking) >= 2)
			{
				computerHand.remove(checking);
				computerHand.remove(checking);
			}
			if(originalSize == computerHand.size())
				spot++;
		}
	}
}

string FishGame::getGuess()
{
	string cardType;
	string cardNumber;
	string card;
	bool existsInPlayerHand = false;

	cout << "What is your guess? " << endl<< endl;
	cout << "Enter card type: (Example: Fish)" << endl;
	cin >> cardType;
	cout << "Enter card number:" << endl;
	cin >> cardNumber;


	if (isNumber(cardNumber) == false)
	{
		cout << "Ivalid guess." << endl << endl;
		return "invalid";
	}

	else
	{
		stringstream cardStream;
		cardStream << cardType << " " << cardNumber;

		existsInPlayerHand = playerHand.nodeExists(cardStream.str());

		if (existsInPlayerHand == false)
		{
			while (existsInPlayerHand == false)
			{
				cout << "You don't have that card in your hand. Please enter another guess." << endl;
				cout << "Enter card type: (Example: Fish)" << endl;
				cin >> cardType;
				cout << "Enter card number:" << endl;
				cin >> cardNumber;

				if (isNumber(cardNumber) == false)
				{
					cout << "Ivalid guess. Try again with the following format, example: Fish 1" << endl << endl;
					return "invalid";
				}

				else
				{
					stringstream cardStream2;
					cardStream2 << cardType << " " << cardNumber;
					existsInPlayerHand = playerHand.nodeExists(cardStream2.str());
					return cardStream2.str();
				}
			}
		}

		else
		{
			return cardStream.str();
		}
	}
}

string FishGame::getComputerGuess()
{
	return computerHand.findLowestPriority();
}

void FishGame::displayDeck()
{
	cout << "Deck: ";

	if(deck.size() == 0)
	{
		cout << "Empty" << endl << endl;
	}

	else
	{
		for (int count = 0; count < deck.size(); count++)
		{
			//cout << "";
			if(count < (deck.size() -1))
				cout << deck.at(count) << ", ";
			//cout << "  WHATEVER  ";
			else
				cout << deck.at(count);

		}

		cout << "" << endl;
	}
}

void FishGame::displayPlayerHand()
{
	cout << "Your Hand: ";
	for (int count = 0; count < playerHand.size(); count++)
	{
		if (count < playerHand.size() - 1)
			cout << playerHand.at(count) << ", ";

		else
			cout << playerHand.at(count);
	}
	cout << endl;
}

void FishGame::displayComputerHand()
{
	cout << "Computer's Hand: ";
	for (int count = 0; count < computerHand.size(); count++)
	{
		if (count < computerHand.size() - 1)
			cout << computerHand.at(count) << ", ";

		else
			cout << computerHand.at(count);
	}
	cout << endl;
}

int FishGame::createDeck(string fileName)
{
	ifstream inRead;
	string unsuccesfull = "Deck could not be created";
	string sucessfull = "Deck was created sucessfully";
	string didNotOpen = "File could not be opened";
	string card;
	string cardType;
	string cardNumber;
	int cardNumberInt;

	inRead.open(fileName.c_str());

	if (inRead.fail())
	{
		cout << "Deck could not be created. Please verify file." << endl << endl;
	}

	else
	{
		if (deck.size() != 0)
			deck.clear();

		while (inRead >> cardType)
		{
			inRead >> cardNumber;

			if (isNumber(cardNumber) == false)
			{
				cout << "Ivalid card found in deck" << endl << "Card discarded" << endl << endl;
			}

			else
			{
				cardNumberInt = atoi(cardNumber.c_str());

				deck.insertHead(cardType, cardNumberInt);
				deck.insertHead(cardType, cardNumberInt);
			}
		}

		displayDeck();
		cout << endl;

		if(deck.size() == 0)
		{
			cout << "Deck could not be created. File was empty." << endl; //empty file
		}
	}

	return deck.size();

}

void FishGame::shuffleDeck()
{
	DoubleLinkedList<string>temp;
	int randomPosition;
	int cardNumber = 0;
	string cardType;
	srand(time(0));

	while (deck.size() > 0)
	{
		cardType = deck.typeAt(0);
		cardNumber = deck.numberAt(0);
		temp.insertHead(cardType, cardNumber);
		deck.remove(deck.at(0));
	}



	while (temp.size() > 0)
	{
		if(temp.size() == 1)
		{
			cardType = temp.typeAt(0);
			cardNumber = temp.numberAt(0);
			deck.insertHead(cardType, cardNumber);
			temp.clear();
		}

		else
		{
			randomPosition = rand() % (temp.size() - 1);
			cardType = temp.typeAt(randomPosition);
			cardNumber = temp.numberAt(randomPosition);
			deck.insertHead(cardType, cardNumber);
			temp.remove(temp.at(randomPosition));
		}
	}

}

//returns the data of the card that was drawn
string FishGame::drawCard(string whichHand)
{
	srand(time(0));
	int randomNumber = 0;
	string cardDrawnType;
	int cardDrawnNumber;

	if(deck.size() > 1)
		randomNumber = rand() % (deck.size() - 1); //checking if size is not 1

	string cardDrawn;

	if(whichHand == "player")
	{
		cardDrawn = deck.at(randomNumber);
		cardDrawnType = deck.typeAt(randomNumber);
		cardDrawnNumber = deck.numberAt(randomNumber);
		playerHand.insertTail(cardDrawnType, cardDrawnNumber);
		deck.remove(cardDrawn);
	}

	else
	{
		cardDrawn = deck.atPlacesFromLast(randomNumber);
		cardDrawnType = deck.placesFromLastTypeAt(randomNumber);
		cardDrawnNumber = deck.placesFromLastNumberAt(randomNumber);
		computerHand.insertTail(cardDrawnType, cardDrawnNumber);
		deck.remove(cardDrawn);
	}

	return cardDrawn;
}

void FishGame::dealCards()
{
	int playerHandSize = playerHand.size();
	int computerHandSize = computerHand.size();

	while (deck.size() > 0 && (playerHand.size() < initialCardSize && computerHand.size() < initialCardSize))
	{
		drawCard("player");
		drawCard("computer");
	}

	deletePairs("player");
	deletePairs("computer");

}

void FishGame::play(int startingHand)
{
	initialCardSize = startingHand;
	int option = 0;
	bool match = false;
	bool inComputerHand = false;
	string cardGuessed;
	string cardDrawn;
	int randomNumber = 0;
	string computerGuess;
	computerScore = 0;
	playerScore = 0;

	int number;
	string type;
	stringstream ss;

	if (deck.size() == 0)
	{
		cout << "Please create a deck before playing" << endl;
	}

	else
	{
		shuffleDeck();
		dealCards();


		do
		{
			displayPlayerHand();
			cout << "Computer's score: " << computerScore << endl;
			cout << "Your score: " << playerScore << endl << endl;

			if (checkSizes() != true) // IF YOU GET ANY BUGS, REMEMBER YOU JUST ADDED THIS
			{
				endGame();
				option = 5;
			}

			else if (checkSizes() == true)
			{
				displayMenu();
				cin >> option;
			}

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input" << endl << endl;
			}

			else if (option == 1)
			{
				cardGuessed = getGuess();

				if (cardGuessed != "invalid") //player's turn
				{
					inComputerHand = computerHand.nodeExists(cardGuessed);

					if (inComputerHand == true)
					{
						cout << "Nice job! Your guess was in the computer's hand!" << endl << endl;
						computerHand.remove(cardGuessed);
						playerHand.remove(cardGuessed);
						playerScore += 3;

						if (checkSizes() != true)
						{
							endGame();
							break;
						}
					}

					else
					{
						cout << "Your guess was not in the computer's hand. Go fish!" << endl << endl;

						ss << cardGuessed;
						ss >> type;
						ss >> number;
						userIncorrectGuesses.insertTail(type, number);
						
						cardDrawn = drawCard("player");
						cout << "You drew card: " << cardDrawn << endl << endl;
						if (playerHand.occurrences(cardDrawn) == 2)
						{
							cout << "You drew a match!" << endl;
							playerHand.remove(cardDrawn);
							playerHand.remove(cardDrawn);
							playerScore++;

							if (checkSizes() != true)
							{
								endGame();
								break;
							}
						}

					} //player's turn ends

					cout << "It's the computer's turn" << endl;
					system("pause");

					//COMPUTER'S TURN STARTS
					//Computer's guess
					//if(computerHand.size()  > 1) //checking that size is not 1
						//randomNumber = rand() % (computerHand.size() - 1);

					//else
						//randomNumber = 0;

					//computerGuess = computerHand.at(randomNumber);

					computerGuess = getComputerGuess();

					cout << endl << "Computer Guess: Do you have a " << computerGuess << "?" << endl;

					if (playerHand.nodeExists(computerGuess) == true)
					{
						cout << "Your response: Yes" << endl << endl;
						playerHand.remove(computerGuess);
						computerHand.remove(computerGuess);
						computerScore += 3;

						if (checkSizes() != true)
						{
							endGame();
							break;
						}
					}

					else
					{
						cout << "Your response: No, go fish!" << endl << endl;

						computerHand.setPriority(computerGuess, 3);

						cardDrawn = drawCard("computer");

						if (computerHand.occurrences(cardDrawn) == 2)
						{
							cout << "Computer drew a match!" << endl << endl;
							computerHand.remove(cardDrawn);
							computerHand.remove(cardDrawn);
							computerScore++;

							if (checkSizes() != true)
							{
								endGame();
								break;
							}
						}

						else if (userIncorrectGuesses.occurrences(cardDrawn) == 1)
						{
							computerHand.setPriority(cardDrawn, 1);
						}
					}
				}
			}

			else if (option == 2)
				shuffleDeck();

			else if (option == 3)
				displayDeck();

			else if (option == 4)
				displayComputerHand();

		} while (option != 5);

		cout << "Thanks for playing!" << endl << endl;
		deck.clear();
		computerHand.clear();
		playerHand.clear();
	}
}
