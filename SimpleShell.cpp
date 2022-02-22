/*
* Katherine Le
* CSCI 411
* Lab: Simple Shell
*/

// C++ declarations
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

// C declarations
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for POSIX

using namespace std;

int main()
{
	// Delete old file history
	string oldFile = "rm ShellResults.txt";
	system(oldFile.c_str());

	// Print a prompt
	printf("This is the shell start. Enter a command. \n");

	// Read command line, parse, and execute
	while(1)
	{
		stringstream ssObject;
		string input;
		string command;

		getline(cin, input);

		ssObject << input;
		ssObject >> command;

		if(input == "quit")
		{
			break;
		}
		else if(input == "myprocess") // myprocess
		{
			string command = "pidof";
			system(command.c_str());
		}
		else
		{
			string inputToFile = input + " >> ShellResults.txt";
			system(inputToFile.c_str());
		}

		// allprocesses

		// chgd <directory> 

		// clr 


		// dir <directory>


		// environ
		// help

		// quit 

		// string inputToFile = input + " >> ShellResults.txt";
		// system(inputToFile.c_str());

	}
	fflush(stdin);

	cout << "End of Shell. Shell History: " << endl;
	string showFile = "cat ShellResults.txt";
	system(showFile.c_str());

	return 0;
}
