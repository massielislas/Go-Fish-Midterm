/*Massiel Islas-Malanco
Proffessor Burton
CS 235 Winter 2017 Midterm.�*/

#pragma once
//#include "LinkedListInterface.h"
#include <sstream>

/*
	Priority 1: User has incorrectly guesssed it before, but the computer drew the card since
	Priority 2: Computer has not guessed this card before
	Priority 3: Computer has guessed this card before, and it has been incorrect
*/

const int DEFAULT_PRIORITY = 2; //making it two means the card has not yet been an incorrect guess

using namespace std;
template<typename T>

class DoubleLinkedListPriorities // public LinkedListInterface<T>
{
private:
	struct Card
	{
		T data;
		int priority;
		int cardNumber;
		string cardType;
		Card* next = NULL;
		Card* previous = NULL;

		Card(string type, int number)
		{
			stringstream ss;
			this->cardType = type;
			this->cardNumber = number;
			ss << cardType << " " << cardNumber;

			this->data = ss.str();

			priority = DEFAULT_PRIORITY;
		}
	};
	Card* head = NULL;



public:
	DoubleLinkedListPriorities(void)
	{
		Card* head = NULL;
	};

	~DoubleLinkedListPriorities(void)
	{
	};

	/*
	find

	Finds a Node who's data is equal to  the parameter value
	*/

	Card* find(T value)
	{
		if (head == NULL)
			return NULL;

		Card* temp = head;

		while (temp->data != value)
		{

			if (temp->next == NULL)
			{
				break;
			}

			temp = temp->next;
		}

		if (temp->data == value)
			return temp;

		else
			return NULL;
	};

	string findLowestPriority()
	{
		Card* temp = head;
		int randomNumber = 0;
		while (temp->priority != 1) //checking for cards that have a 1 priority
		{
			if (temp->next == NULL)
			{
				break;
			}
			
			temp = temp->next;
		}

		if (temp->priority == 1)
			return temp->data;

		while (temp->priority != 2) //checking for cards that have a 2 priority
		{
			if (temp->next == NULL)
			{
				break;
			}

			temp = temp->next;
		}

		if (temp->priority == 2)
			return temp->data;

		if (size() > 1)		//return random number if there are only priority 3 cards
			randomNumber = rand() % (size() - 1);

		//temp = at(randomNumber);

		return at(randomNumber);

		/*
		if(computerHand.size()  > 1) //checking that size is not 1
		randomNumber = rand() % (computerHand.size() - 1);

		else
		randomNumber = 0;
		*/
	}

	int occurrences(T checkingFor)
	{
		int howMany = 0;

		if (head == NULL)
			return 0;

		Card*temp = head;

		while (temp->next != NULL)
		{
			if (temp->data == checkingFor)
			{
				howMany++;
			}

			temp = temp->next;
		}

		if (temp->data == checkingFor)
		{
			howMany++;
		}

		return howMany;
	};

	bool nodeExists(T value)
	{
		if (head == NULL)
			return NULL;

		Card* temp = head;

		while (temp->data != value)
		{

			if (temp->next == NULL)
			{
				break;
			}

			temp = temp->next;
		}

		if (temp->data == value)
			return true;

		else
			return false;
	}

	void setPriority(T data, int priority)
	{
		Card* cardToSet = find(data);
		cardToSet->priority = priority;
	}

	int getCardNumber(Card thisCard)
	{
		return thisCard->cardNumber;
	}

	string getCardType(Card thisCard)
	{
		return thisCard->cardType;
	}

	int getPriority(Card thisCard)
	{
		return thisCard->priority;
	}

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(string type, int number)
	{
		Card* new_Node = new Card(type, number);

		if (head == NULL)
		{
			head = new_Node;
			new_Node->next = NULL;
			new_Node->previous = NULL;
		}

		else
		{

			new_Node->next = head;
			head = new_Node;
			new_Node->previous = NULL;
			Card* second = new_Node->next;
			second->previous = new_Node;
		}

	};

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(string type, int number)
	{
		if (head == NULL)
		{
			insertHead(type, number);
		}

		else
		{

			Card* new_Node = new Card(type, number);

			Card* temp = head;

			while (temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = new_Node;
			new_Node->previous = temp;

		}
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(string type, int number, T insertionNode)
	{

		if (head != NULL)
		{
			Card* temp = NULL;
			temp = find(insertionNode);

			if (temp != NULL)
			{
				Card* new_Node = new Card(type, number);
				new_Node->next = temp->next;
				new_Node->previous = temp;
				temp->next = new_Node;

				if (new_Node->next != NULL) //if there is something after this Node
				{
					Card* second = new_Node->next;
					second->previous = new_Node;
				}
			}
		}
	};

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value)
	{
		if (head != NULL)
		{
			Card* to_delete = NULL; //node used to find the one we want to delete
			to_delete = find(value);

			if (to_delete != NULL) //checking that what we want to remove is actually there
			{
				if (to_delete == head) //case where you want to delete the head
				{
					head = head->next;
					delete to_delete;
				}

				else
				{
					Card* one_before = head;

					while (one_before->next != to_delete)
						one_before = one_before->next;

					one_before->next = to_delete->next;

					if (to_delete->next != NULL)
					{
						Card* second = one_before->next;
						second->previous = one_before;
					}


					delete to_delete;
				}

			}
		}
	};

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear()
	{
		if (head != NULL)
		{
			while (head->next != NULL) //deleting all except the last one;
				remove(head->data);

			remove(head->data);

			head = NULL;
		}
	};

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size()
	{
		if (head == NULL)
		{
			return 0;
		}

		else
		{
			int size = 0;
			Card* temp = head;

			while (temp->next != NULL)
			{
				size++;
				temp = temp->next;
			}

			size++;

			return size;
		}
	};

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index)
	{
		int list_size = size();
		int minimum_index = 0;
		int maximum_index = 0;
		maximum_index = size();

		Card* temp = head;

		for (int count = 0; count < index; count++)
			temp = temp->next;

		return temp->data;
	};

	string typeAt(int index)
	{
		int list_size = size();
		int minimum_index = 0;
		int maximum_index = 0;
		maximum_index = size();

		Card* temp = head;

		for (int count = 0; count < index; count++)
			temp = temp->next;

		return temp->cardType;
	};

	int numberAt(int index)
	{
		int list_size = size();
		int minimum_index = 0;
		int maximum_index = 0;
		maximum_index = size();

		Card* temp = head;

		for (int count = 0; count < index; count++)
			temp = temp->next;

		return temp->cardNumber;
	};

	T atPlacesFromLast(int index)
	{
		int list_size = size();
		int minimum_index = 0;
		int maximum_index = 0;
		maximum_index = size();

		if (head == NULL || list_size == 0 || index < minimum_index || index > maximum_index)
		{
			throw out_of_range(" ");
		}

		else
		{
			Card* temp = head;

			while (temp->next != NULL) //finding tail
			{
				temp = temp->next;
			}

			for (int count = 0; count < index; count++)
				temp = temp->previous;

			return temp->data;
		}
	};


	string placesFromLastTypeAt(int index)
	{
		int list_size = size();
		int minimum_index = 0;
		int maximum_index = 0;
		maximum_index = size();

		if (head == NULL || list_size == 0 || index < minimum_index || index > maximum_index)
		{
			throw out_of_range(" ");
		}

		else
		{
			Card* temp = head;

			while (temp->next != NULL) //finding tail
			{
				temp = temp->next;
			}

			for (int count = 0; count < index; count++)
				temp = temp->previous;

			return temp->cardType;
		}
	};

	int placesFromLastNumberAt(int index)
	{
		int list_size = size();
		int minimum_index = 0;
		int maximum_index = 0;
		maximum_index = size();

		if (head == NULL || list_size == 0 || index < minimum_index || index > maximum_index)
		{
			throw out_of_range(" ");
		}

		else
		{
			Card* temp = head;

			while (temp->next != NULL) //finding tail
			{
				temp = temp->next;
			}

			for (int count = 0; count < index; count++)
				temp = temp->previous;

			return temp->cardNumber;
		}
	};


	string toString()
	{

		stringstream ss("");
		if (head != NULL)
		{
			Card* temp = head;

			while (temp->next != NULL)
			{
				ss << temp->data << " ";
				temp = temp->next;
			}

			ss << temp->data;

			return ss.str();
		}

		return ss.str();
	};

};
