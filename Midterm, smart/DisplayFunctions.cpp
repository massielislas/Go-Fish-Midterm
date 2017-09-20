#pragma once

#include "DisplayFunctions.h"

using namespace std;

void DisplayFunctions::displayAsciiArt()
{
	ifstream inRead;
	string fileName = "art.txt";
	string line;

	inRead.open(fileName.c_str());

	while (getline(inRead, line))
	{
		cout << line << endl;
	}
}

void DisplayFunctions::writeWithCout()
{
	ifstream inRead;
	ofstream outWrite;
	string fileName;
	stringstream ss;
	string line;

	cout << "Enter the name of the file you would like to translate" << std::endl;
	cin >> fileName;

	inRead.open(fileName.c_str());

	while (inRead.fail())
	{
		cout << "The file does not exist." << endl
			<< "Please enter the name of an existing file" << endl;
		cin >> fileName;
		inRead.open(fileName.c_str());
	}

	outWrite.open("out_file.txt");

	cin.ignore();

	while (std::getline(inRead, line))
	{
		std::string newLine;
		newLine += "cout << \" " + line + " \" << endl;" + '\n';
		std::cout << newLine;
		outWrite << newLine;
	}
}