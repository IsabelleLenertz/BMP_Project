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
	int* pWidth = new int;
	int* pHeight = new int;
	int* pBitesPerPixel = new int;
	int bytePerPixel = 0;
	int paddingPerLine = 0;

	reader.open("FF49-20.bmp", ios::binary);
	if( reader.is_open() == true )
	{
		cout << "The file was found." << endl;
	}
	else
	{
		cout << "The file could not be open." << endl;
		cout << "Emergency exit." << endl;
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

	// Calculate the number f padding bytes per line (a line has to end with a multiple of 4 bytes)
	paddingPerLine = 4-(*pWidth)*bytePerPixel%4;
	cout << "Padding per line: " << paddingPerLine << endl;


	return 0;
}
