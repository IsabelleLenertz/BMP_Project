//============================================================================
// Name        : BMPproject.cpp
// Author      : Isabelle Delmas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Utilities.hpp"
#include "InsertMessage.hpp"
#include "PixelArrayExt.hpp"

using namespace std;

int main() {

	string fileAddress = ""; // Used to store the address of the file to modify
	string message = ""; // Used to store message to hide
	InsertMessage * pInsert = nullptr; // Insertion object
	PixelArrayExt * pRetrieve = nullptr;


	cout << "Welcome." << endl;
	cout << "This software has been designed to hide text messages into a BMP file."<< endl;
	cout << "Please indicate the relative address of the file (starting from the file BMP_Projectaddress)," << endl;
	cout << "or place your file inside the 'BMP_Project'." << endl;
	cout << "For now, you may use only 24bites BMP files." << endl;
	fileAddress = Utilities::inputString("Address :",1, 200 );
	message = Utilities::inputString("Message to hide :",1, 200 );

	pInsert = new InsertMessage(fileAddress, message);

	try{
		if (pInsert->insertMessage() == true){
			cout << "The message has been inserted." << endl;
			cout << "You may use a binary viewer to look at you file." << endl;

		}
	}
	catch (MessageTooLong & error){
		cout << "Your message is too long" << endl;
		cout << "This image cannot hold more than " << pInsert->maxMessageSize() << " characters" << endl;
	}


	cout << "You may retrieve a message hidden in a BMP file." << endl;
	cout << "For now, you may use only 24bites BMP files." << endl;
	fileAddress = Utilities::inputString("Address :",1, 200 );
	pRetrieve = new PixelArrayExt(fileAddress);
	message = pRetrieve->extractMessage();
	cout << "The message is: " << endl;
	cout << message << endl;


	cout << "Thank you for using this software." << endl;
	cout << "Have a nice day." << endl;

	delete pInsert;
	delete pRetrieve;
}


