//============================================================================
// Name        : BMPproject.cpp
// Author      : Isabelle Delmas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream reader;
	ofstream writer;
	int* pWidth = new int;
	int* pHeight = new int;
	int* pBitesPerPixel = new int;
	int bytePerPixel = 0;
	int paddingPerLine = 0;
	int paddingAvailable =0;
	int pixelArrayStartingAddress = 54; // for 24 bites BMP only
	string message = "Tralala PomPom";
	char* pMessage = new char;
	*pMessage = 'a';

	/*
	 * EXCTRATIING USEFUL DATA FROM THE HEADER FILE
	 */

	reader.open("FF49-20.bmp", ios::binary);
	if( reader.is_open() == true )
	{
		cout << "The file was found." << endl;
	}
	else
	{
		cout << "The file could not be open." << endl;
		cout << "Emergency exit." << endl;
		delete pMessage;
		delete pWidth ;
		delete pHeight;
		delete pBitesPerPixel;
		return 0;
	}

	// Reads the width of the image
	reader.seekg(18);
	reader.read(reinterpret_cast<char*>(pWidth), 4);
	cout << "The width of the image is: " << *pWidth << endl;

	// Reads the height of the image
	reader.seekg(22);
	reader.read(reinterpret_cast<char*>(pHeight), 4);
	cout << "The height of the image is: "<< *pHeight << endl;

	// Reads the number of bites per pixel
	reader.seekg(28);
	reader.read(reinterpret_cast<char*>(pBitesPerPixel), 4);
	cout << "Bites per pixel: " << *pBitesPerPixel<<  endl;

	// Calculate the number of Bytes per pixel
	bytePerPixel = *pBitesPerPixel/8;
	cout <<"Bytes per pixel: " << bytePerPixel << endl;

	// Calculate the number of padding bytes per line (a line has to end with a multiple of 4 bytes)
	if ((*pWidth)*bytePerPixel%4 == 0){
		paddingPerLine = 0;
	}
	else {
		paddingPerLine = 4-(*pWidth)*bytePerPixel%4;
	}
	cout << "Padding per line: " << paddingPerLine << endl;

	// Calculate the number of padding bytes in the entire file.
	paddingAvailable = paddingPerLine*(*pHeight);
	cout << "padding in the image: " << paddingAvailable << endl;

	// Closes the reader
	reader.close();

	// stores the addresses of the beginning of the padding bytes of each line.
	int lineAddress [*pHeight];
	lineAddress[0] = pixelArrayStartingAddress + (*pWidth)*bytePerPixel;
	for (int i = 1; i < *pHeight; i++){
		lineAddress[i] = pixelArrayStartingAddress + (*pWidth)*bytePerPixel*(i+1) + paddingPerLine*i;
	}


	/*
	 * INSERTING A MESSAGE
	 */

	// Checks if there are enough bytes available for the message.
	// Prints an error message if not enough bytes available
	if ( paddingAvailable < (int)message.size() ){
		cout << "Message too long, please choose another image or change your message." << endl;
		cout << "Size of the message: " << message.size() << " characters" << endl;
		cout << "Padding bytes available in this image: " << paddingAvailable << " byte(s)" << endl;
	}
	// Else inserts the message character by character.
	else{
		// Inserting a char into the padding bytes.
		writer.open("FF49-20.bmp", ios::out | ios::in | ios::binary);
		if (writer.is_open() == true){
			cout << "File was open." << endl;
			int i = 0;
			// check if the end of the message was reached
			while (i <= (int)message.size() ){
				// keeps track of the current lin
				for (int j = 0; j < *pHeight ; j++){
					// Keeps track of the current padding byte within the current line
					for (int k = 0; k < paddingPerLine; k++){
						// places the writing position at the current line (j), at the current padding byte (k)
						writer.seekp(lineAddress[j] + (k) );
						// write the current character (i)
						writer.write(&message[i], 1);
						// moves on to the next character.
						i++;
					}
				}
			}
		}
		// Is the file could not be opened
		else{
			cout << "Could not open file for input" << endl;
		}// end of else
	}

	//Closes the writer
	writer.close();


	/*
	 * READING A MESSAGE
	 */
	// Opens the reader
	reader.open("FF49-20.bmp", ios::binary);
	string hidenMessage = "";
	char tempChar;

	if (reader.is_open() == true){
		cout << "File was open to read a message." << endl;
	}
	else {
		cout << "Could not open the file to read a message." << endl;
		cout << "emergency exit" << endl;

		delete pMessage;
		delete pWidth ;
		delete pHeight;
		delete pBitesPerPixel;
		return 0;
	}
	if (paddingAvailable != 0){
		cout << "Ready to read." << endl;
		//reader.seekg(201);
		//reader.get(tempChar);
		//hidenMessage += TempChar;
		// keeps track of the current line
		for (int j = 0; j < *pHeight ; j++){
			// Keeps track of the current padding byte within the current line
			for (int k = 0; k < paddingPerLine; k++){
				// places the writing position at the current line (j), at the current padding byte (k)
				reader.seekg(lineAddress[j] + (k) );
				// reads the current character and stores it temporary.
				reader.get(tempChar);
				// Adds the char to the message
				hidenMessage += tempChar;
			} // end of for
		} // end of for

		cout << "Your secret message is: " << hidenMessage << endl;
	}// end of if
	else{
		cout << "There are no padding bytes available to hide a message" << endl;
	}

	cout << "Enf od program." << endl;

	delete pMessage;
	delete pWidth ;
	delete pHeight;
	delete pBitesPerPixel;

	return 0;
}


