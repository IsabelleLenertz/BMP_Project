//*****************

//Project Name: Project #5: Employee Linked List

//Project Description: Optimize employee list using a linked list instead of a vector.

//Project Author: Lenertz Isabelle

//Is this an extra credit Project:  No

//Date completed: 11/11/2015

//Operating system used: Windows 10

//IDE Used:  Eclipse

//*****************


#ifndef __CPPUtilities__utilities__
#define __CPPUtilities__utilities__

#include <cmath>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

//
//Prototypes for utilities.cpp
//
class Utilities
{
public:
	// Default constructor
	Utilities();
	// Default destructor
	~Utilities();

	//Change all characters in a string to uppercases
	string static makeUpperCase(string);

	//Change all characters in a string to lowercases
	string static makeLowerCase(string);

	//Input a string to be returned to the calling function.
	//string promtString: message displayed, promoting the user for a string
	//int minLength: minimum length of the string the user should enter
	//int maxLength: maximum length of the string the user should enter
	string static inputString(string, int, int);

	//Input a integer value to be returned to the calling function.  Also, validate the
	//the minimum and maximum value of the integer input.
	int static inputInt(string, int, int, int);

	//Input a double value to be returned to the calling function.  Also, validate the
	//the minimum and maximum value of the double input.
	double static inputDouble(string, double, double, double);

	//Send a string and center it in a returned string
	string static centerString(string, int);

	// This function will return a random integer no larger than Max
	int static getRandomInt(int, int);

	//This function will return a random double with 2 decimal digits, and not greater than Max
	double static getRandomDouble(int, int, int);

	// This function will return a random integer no larger than Max
	string static getRandomString(int, int);

	//Display a prompt asking the user if they want to
	//sort the vector ascending or descening.
	bool static verifyAction(string);

	//Ask the user if they want to append, overwrite or quit the read operation
	char static askOverWrite(void);


private:
	//Clear the CIN input buffer to avoid problems
	void static clearCIN(void);

};


#endif /* defined(__CPPUtilities__utilities__) */
