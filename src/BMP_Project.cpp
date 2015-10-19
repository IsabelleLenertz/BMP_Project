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
	char* pMessage = new char;
	*pMessage = 'a';

	reader.open("FF49-20.bmp", ios::binary);
	if( reader.is_open() == true )
	{
		cout << "The file was found." << endl;
	}
	/*else
	{
		cout << "The file could not be open." << endl;
		cout << "Emergency exit." << endl;
		return 0;
	}*/

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
	paddingPerLine = 4-(*pWidth)*bytePerPixel%4;
	cout << "Padding per line: " << paddingPerLine << endl;

	// Calculate the number of padding bytes in the entire file.
	paddingAvailable = paddingPerLine*(*pHeight);
	cout << "padding in the image: " << paddingAvailable << endl;

	// Closes the reader
	reader.close();

	// Inserting a char into the padding bytes.
	writer.open("FF49-20.bmp", ios::binary);
	if (writer.is_open() == true){
		cout << "File was open, input : a" << endl;
		writer.seekp(pixelArrayStartingAddress);
		writer.write(pMessage, 1);
	}
	else{
		cout << "Could not open file for input" << endl;
	}

	//Closes the writer
	writer.close();
	return 0;
}
