/*Massiel Islas-Malanco
Proffessor Burton
CS 235 Winter 2017 Midterm.*/

#pragma once
#include "DoubleLinkedList.h"
#include "DoubleLinkedListPriorities.h"
#include <string>


class FishGame
{
private:
	DoubleLinkedList<string>userIncorrectGuesses;
	DoubleLinkedListPriorities<string> computerHand;
	int computerScore;
	DoubleLinkedList<string> playerHand;
	int playerScore;
	DoubleLinkedList<string> deck;
	int initialCardSize;

	void deletePairs(string);
	bool checkSizes();
	void displayMenu();
	string getGuess();
	string getComputerGuess();
	void endGame();
	bool isNumber(string);

public:
	FishGame()
	{
		initialCardSize = 0;
		computerScore = 0;
		playerScore = 0;
	};
	~FishGame() {};
	int createDeck(string);
	void shuffleDeck();
	string drawCard(string);
	void dealCards();
	void play(int);
	void displayDeck();
	void displayPlayerHand();
	void displayComputerHand();

};
